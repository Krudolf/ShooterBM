// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicated(true);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	OnTakeDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(UHealthComponent, Health);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
}

void UHealthComponent::TakeDamage(const float Damage)
{
	Health = FMath::Max(Health - Damage, 0.f);

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

void UHealthComponent::Heal(const float HealAmount)
{
	Health = FMath::Min(Health + HealAmount, MaxHealth);
}

float UHealthComponent::GetHealthNormalized() const
{
	return Health / MaxHealth;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::ResetHealth()
{
	Health = MaxHealth;
}

