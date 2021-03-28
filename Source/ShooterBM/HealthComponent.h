// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamage, float, Damage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERBM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	float Health = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.f;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(const float Damage);

	UFUNCTION(Server, Reliable)
	void ServerTakeDamage(const float Damage);

	UFUNCTION(BlueprintCallable)
	void Heal(const float HealAmount);

	UFUNCTION(BlueprintCallable)
	float GetHealthNormalized() const;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealth() const { return Health;}

	UFUNCTION(BlueprintCallable)
	void ResetHealth();
};
