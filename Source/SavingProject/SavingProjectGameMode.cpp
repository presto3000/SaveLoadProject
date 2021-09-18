// Copyright Epic Games, Inc. All Rights Reserved.

#include "SavingProjectGameMode.h"

#include "SaveManager.h"
#include "SavingProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASavingProjectGameMode::ASavingProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASavingProjectGameMode::InitGameState()
{
	USaveManager::QueryAllSaveInterfaces();
	USaveManager::LoadGame();

	Super::InitGameState();
}
