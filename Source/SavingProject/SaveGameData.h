// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

/**
 * //SAVES ** INFO ** ABOUT THE GAME //
 */

//Struct://////////////
USTRUCT()
struct FSaveData
{
	GENERATED_BODY()
	//some kind of buffer Array for data, place to store it
	UPROPERTY(VisibleAnywhere)
	TArray<uint8> Data;
};


///////////////////////
UCLASS()
class SAVINGPROJECT_API USaveGameData : public USaveGame
{
	GENERATED_BODY()

	public:
	UPROPERTY(VisibleAnywhere)
	TMap<FString, FSaveData> SerializedData;
	
	
	
};
