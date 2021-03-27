// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterBMGameMode.h"
#include "ShooterBMHUD.h"
#include "ShooterBMPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AShooterBMGameMode::AShooterBMGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterBMHUD::StaticClass();
	PlayerControllerClass = AShooterBMPlayerController::StaticClass();
}

void AShooterBMGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), OutSpawnPoints);

	for(AActor* ActorSpawnPoint : OutSpawnPoints)
	{
		if(ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(ActorSpawnPoint))
		{
			SpawnPoints.Add(SpawnPoint);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("SpawnPoints found: %i"), SpawnPoints.Num());
}

ASpawnPoint* AShooterBMGameMode::GetRandomSpawnPoint()
{
	const int32 Index = FMath::RandRange(0, SpawnPoints.Num() - 1);

	return SpawnPoints[Index];
}
