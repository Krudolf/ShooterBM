// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "SpawnPoint.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterBMGameMode.generated.h"

UCLASS(minimalapi)
class AShooterBMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterBMGameMode();

	virtual void BeginPlay() override;

	ASpawnPoint* GetRandomSpawnPoint();

private:
	UPROPERTY()
	TArray<ASpawnPoint*> SpawnPoints;
	
};



