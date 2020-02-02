// Fill out your copyright notice in the Description page of Project Settings.


#include "api_socket.h"

// Sets default values
Aapi_socket::Aapi_socket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aapi_socket::BeginPlay()
{
	Super::BeginPlay();
	
	SetRainIntensity(0.f);
	SetDayLength(1.f);
	CreateFetchQuest(3);
	CreateFetchQuest(2);
	
	StartUDPReceiver("Bio-Sensor Receiver", "127.0.0.1", 60221);
}

// Called every frame
void Aapi_socket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aapi_socket::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//~~~~~~~~~~~~~~~~

	delete UDPReceiver;

	// Clear all sockets!
	// makes sure repeat plays in Editor dont hold on to old sockets!
	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Rama's Start UDP Receiver
bool Aapi_socket::StartUDPReceiver(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort
) {

	ScreenMsg("RECEIVER INIT");

	//~~~

	FIPv4Address Addr;
	FIPv4Address::Parse(TheIP, Addr);

	//Create Socket
	FIPv4Endpoint Endpoint(Addr, ThePort);

	//BUFFER SIZE
	int32 BufferSize = 2 * 1024 * 1024;

	ListenSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(BufferSize);

	FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(100);
	UDPReceiver = new FUdpSocketReceiver(ListenSocket, ThreadWaitTime, TEXT("UDP RECEIVER"));
	UDPReceiver->OnDataReceived().BindUObject(this, &Aapi_socket::Recv);
	UDPReceiver->Start();

	return true;
}

void Aapi_socket::Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt)
{
	ScreenMsg("Received bytes", ArrayReaderPtr->Num());

	// Copy the data to a mutable buffer
	TArray<uint8> rawData;
	rawData.Init(0, ArrayReaderPtr->Num());
	for (int i = ArrayReaderPtr->Num() - 1; i >= 0; --i) {
		rawData[i] = ArrayReaderPtr->Pop();
	}

	// Convert the data into a string
	FString parsedMessage = StringFromBinaryArray(rawData);
	ScreenMsg("Message= ", parsedMessage);

	// Convert the string into a packet
	UDPPacket packet;
	CreatePacket(&packet, parsedMessage);
	ScreenMsg(packet);

	// Call function to handle this new message
	ProcessPacket(packet);
}

//Rama's String From Binary Array
FString Aapi_socket::StringFromBinaryArray(TArray<uint8> BinaryArray)
{
	BinaryArray.Add(0); // Add 0 termination. Even if the string is already 0-terminated, it doesn't change the results.
	// Create a string from a byte array. The string is expected to be 0 terminated (i.e. a byte set to 0).
	// Use UTF8_TO_TCHAR if needed.
	// If you happen to know the data is UTF-16 (USC2) formatted, you do not need any conversion to begin with.
	// Otherwise you might have to write your own conversion algorithm to convert between multilingual UTF-16 planes.
	return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
}

void Aapi_socket::CreatePacket(UDPPacket* out, FString& data)
{
	// Split the string on all semiciolons
	TArray<FString> tokenizedString;
	data.ParseIntoArray(tokenizedString, TEXT(";"));

	// Store the metadata
	out->m_sequenceNumber = FCString::Atoi(*tokenizedString[0]);
	out->m_eventSource = tokenizedString[1];
	out->m_sampleName = tokenizedString[2];
	out->m_timeStamp = FCString::Atoi(*tokenizedString[3]);
	out->m_mediaTime = FCString::Atoi(*tokenizedString[4]);
	
	// Remove these first 5 entries
	tokenizedString.RemoveAt(0, 5, true);
	
	// Store the raw data
	out->m_rawData = tokenizedString;
}

void Aapi_socket::ProcessPacket(UDPPacket& packet)
{
	if (packet.m_eventSource == "EyeTracker") {
		if (packet.m_sampleName == "EyeData") {
			if (packet.m_sampleName.Len()) {
				SetRainIntensity(0.5f);
			}
		}
	}
}