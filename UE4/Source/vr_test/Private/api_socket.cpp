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
	
	OpenConnection();
}

// Called every frame
void Aapi_socket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// TCP Listener
bool Aapi_socket::OpenConnection() {

	FIPv4Endpoint Endpoint(FIPv4Address(127, 0, 0, 1), 60221);

	Listener = new FTcpListener(Endpoint, FTimespan(8));

	//Set Buffer Size
	Listener->OnConnectionAccepted().BindUObject(this, &Aapi_socket::RecieveMessages);

	Listener->Init();


	return true;
}

bool Aapi_socket::RecieveMessages(FSocket* socket, const FIPv4Endpoint& enpoint) {

	if (!socket) {
		return false;
	}

	ConnectionSocket = socket;

	GetWorldTimerManager().SetTimer(timer, this, &Aapi_socket::TCPSocketListener, 0.01, true);

	return true;
}

void Aapi_socket::TCPSocketListener() {
	if (!ConnectionSocket) {
		return;
	}


	//Binary Array!
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (ConnectionSocket->HasPendingData(Size))
	{
		ReceivedData.Init(0, Size);

		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	}

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}

	if (ReceivedData[0] == 10 && ReceivedData[1] == 10 && ReceivedData[2] == 10 && ReceivedData[3]) {
		float f;
		char b[] = { ReceivedData[7], ReceivedData[6], ReceivedData[5], ReceivedData[4] };
		memcpy(&f, &b, sizeof(f));
		SetRainIntensity(f);
	}
}