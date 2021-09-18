// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveMetadata.h"
#include "UObject/NoExportTypes.h"
#include "SaveManager.generated.h"

/**
 * 
 */
UCLASS()
class SAVINGPROJECT_API USaveManager : public UObject
{
	GENERATED_BODY()

private:
	// The current save slot // static var should be Decleared in Cpp too
	static FString CurrentSaveSlot;

public:
	// Initialize the class. Must be called when the game first launches
	static void Init();

	// Queries all the actors in the game that implement the save interface
	static void QueryAllSaveInterfaces();

	// Saves the current state of the game
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void SaveGame();

	// Loads the current state of the game
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void LoadGame();
	
	// Deletes the specified slot
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void DeleteSlot(const FString& slot);

	// Gets a new, unused slot
	UFUNCTION(BlueprintPure, Category = "SavingAndLoading")
	static UPARAM(DisplayName = "Slot") FString GetNewSaveSlot(bool& slot_found);

	// Sets the current save slot to the specified value
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void SetCurrentSaveSlot(const FString& slot);

	// Gets the current save slot to the specified value
	UFUNCTION(BlueprintPure, Category = "SavingAndLoading")
	static FString GetCurrentSaveSlot();

	// Gets all the saved games
	UFUNCTION(BlueprintPure, Category = "SavingAndLoading")
	static TArray<FSaveMetadata> GetAllSaveMetadata();
};
