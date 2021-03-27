// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterBMProjectile.h"

#include "ShooterBMCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AShooterBMProjectile::AShooterBMProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShooterBMProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	
	SetReplicates(true);
	SetReplicateMovement(true);
}

void AShooterBMProjectile::OnHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if (HasAuthority() && OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		bool bDestroy = false;
		if(OtherComp->IsSimulatingPhysics())
		{
			bDestroy = true;
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());			
		}

		AShooterBMCharacter* Player = Cast<AShooterBMCharacter>(OtherActor);
		if(Player != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Player hitted"));
			Player->TakeDamage(Damage, FDamageEvent(), GetOwner()->GetInstigatorController(), Player);
			bDestroy = true;
		}
		
		if(bDestroy)
		{
			Destroy();	
		}
	}
}