// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SaveMetadata.generated.h"



USTRUCT(BlueprintType)
struct FSaveMetadata
{
	GENERATED_BODY()
	// The name of the slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	FString SlotName;

	// The date that slot was created or the game was saved 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	FDateTime Date;


	



	
};