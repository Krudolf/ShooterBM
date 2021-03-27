// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterBMPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERBM_API AShooterBMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterBMPlayerController();

	UFUNCTION(Server, Reliable)
    void Respawn();

	FTimerHandle RespawnHandle;
	
protected:
	void Spawn();

};
