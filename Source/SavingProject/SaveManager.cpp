// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"

#include "SaveGameData.h"
#include "SaveGameMetadata.h"
#include "Kismet/GameplayStatics.h"

FString USaveManager::CurrentSaveSlot;
static const FString kMetadataSaveSlot = "SaveGameMetadata";
static const int32 kMaxSaveSlots = 100;

void USaveManager::Init()
{
	CurrentSaveSlot = "Default";

	// Make sure the metadata file exists in case the game has never been ran
	USaveGame* saveGameMetadata = UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0);

	if(saveGameMetadata == nullptr)
	{
	// Since the metdadata file doesn't exist, we need to create one
	USaveGame* saveGameObject =	UGameplayStatics::CreateSaveGameObject(USaveGameMetadata::StaticClass());

	UGameplayStatics::SaveGameToSlot(saveGameObject, kMetadataSaveSlot, 0);	
	}
}

void USaveManager::QueryAllSaveInterfaces()
{
	// TODO
}

void USaveManager::SaveGame()
{
	// Create a new save game data instance
	USaveGameData* saveGameData = Cast<USaveGameData>( UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));

	// TODO :: Go over all the actors that need to be saved and save them

	// Save the game to the current slot
	UGameplayStatics::SaveGameToSlot(saveGameData, CurrentSaveSlot, 0);

	// Update the metadata file with the new slot
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>( UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));

	FSaveMetadata& saveMetadata = saveGameMetadata->SavedGameMetadata.FindOrAdd(CurrentSaveSlot);
	saveMetadata.SlotName = CurrentSaveSlot;
	saveMetadata.Date = FDateTime::Now();

	// Save the changes to the metadata file
	UGameplayStatics::SaveGameToSlot(saveGameMetadata, kMetadataSaveSlot, 0);

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Saved: " + CurrentSaveSlot);
	}
}

void USaveManager::LoadGame()
{
	USaveGameData* saveGameData = Cast<USaveGameData>(  UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0));

	if(saveGameData == nullptr)
	{
		// No saves exist yet for this slot. SAve a default one.
		SaveGame();

		// Reload it
		saveGameData = Cast<USaveGameData>(  UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0));
	}

	//TODO:: Loop over all the actors that need to load data and load their data
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Loaded: " + CurrentSaveSlot);
	}
}

void USaveManager::DeleteSlot(const FString& slot)
{
	//Delete the slot
	UGameplayStatics::DeleteGameInSlot(slot, 0);

	// Loading the metadata slot
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>( UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));

	saveGameMetadata->SavedGameMetadata.Remove(slot);

	//Save the metadata slot after removing the slot
	UGameplayStatics::SaveGameToSlot(saveGameMetadata, kMetadataSaveSlot, 0);
}

FString USaveManager::GetNewSaveSlot(bool& slot_found)
{
	slot_found = false;

	// Loading the metadata file
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>( UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));

	for (int32 i =0; i < kMaxSaveSlots; ++i)
	{
		// SaveSlot0, SaveSlot1, etc...
		FString slotName = "SaveSlot" + FString::FromInt(i);

		if(saveGameMetadata->SavedGameMetadata.Contains(slotName) == false)
		{
			//We found a free slot! Return it
			slot_found = true;
			return slotName;
		}
	}
	
	return  FString();
}

void USaveManager::SetCurrentSaveSlot(const FString& slot)
{
	CurrentSaveSlot = slot;
}

FString USaveManager::GetCurrentSaveSlot()
{
	return CurrentSaveSlot;
}

TArray<FSaveMetadata> USaveManager::GetAllSaveMetadata()
{
	TArray<FSaveMetadata> metadata;
	// Loading the metadata file
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>( UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));
	metadata.Reserve(saveGameMetadata->SavedGameMetadata.Num());

	// Add each saved game's metadata to the return array
	for (const auto& saved_game : saveGameMetadata->SavedGameMetadata)
	{
		metadata.Push(saved_game.Value);
	}

	return metadata;
}
