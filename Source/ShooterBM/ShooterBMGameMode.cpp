// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterBMGameMode.h"
#include "ShooterBMHUD.h"
#include "ShooterBMCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterBMGameMode::AShooterBMGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterBMHUD::StaticClass();
}
