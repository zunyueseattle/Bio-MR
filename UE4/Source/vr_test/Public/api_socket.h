// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "api_socket.generated.h"

UCLASS()
class VR_TEST_API Aapi_socket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aapi_socket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetRainIntensity(float rain);

	UFUNCTION(BlueprintImplementableEvent)
	void SetDayLength(float minutes);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFetchQuest(int items);
};
