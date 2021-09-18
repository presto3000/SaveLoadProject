// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SavingProjectGameMode.generated.h"

UCLASS(minimalapi)
class ASavingProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASavingProjectGameMode();

	virtual void InitGameState() override;
	
};



