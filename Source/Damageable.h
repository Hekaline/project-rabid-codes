// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_RABID_5_3_API IDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) = 0;

	UFUNCTION()
	virtual void OnDeath(AActor* DeathCauser) = 0;
	
public:
};
