// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterBMPlayerController.h"

#include "ShooterBMGameMode.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"


AShooterBMPlayerController::AShooterBMPlayerController()
{

}

void AShooterBMPlayerController::Respawn_Implementation()
{
	DisableInput(this);
	GetWorld()->GetTimerManager().SetTimer(RespawnHandle, this, &AShooterBMPlayerController::Spawn, 10.f, false);
}

void AShooterBMPlayerController::Spawn()
{
	if(AShooterBMGameMode* GameMode = Cast<AShooterBMGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASpawnPoint* SpawnPoint = GameMode->GetRandomSpawnPoint();
		if(APawn* NewPawn = GetWorld()->SpawnActor<APawn>(GameMode->DefaultPawnClass, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation()))
		{
			this->Possess(NewPawn);
			EnableInput(this);
		}		
	}
}