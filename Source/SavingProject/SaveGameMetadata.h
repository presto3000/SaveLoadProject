// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveMetadata.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameMetadata.generated.h"

/**
 * 
 */
UCLASS()
class SAVINGPROJECT_API USaveGameMetadata : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Default")
	TMap<FString, FSaveMetadata> SavedGameMetadata;
};
