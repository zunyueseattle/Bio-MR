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
}

// Called every frame
void Aapi_socket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

