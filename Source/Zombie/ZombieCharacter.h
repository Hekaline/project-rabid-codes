// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../LivingEntity.h"
#include "ZombieCharacter.generated.h"

class APlayerCharacter;
class USphereComponent;
/**
 * 
 */
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitDelegate);
UCLASS()
class PROJECT_RABID_5_3_API AZombieCharacter : public ALivingEntity
{
	GENERATED_BODY()

public:
	AZombieCharacter();
	
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintCallable)
	float GetDamage() const { return AttackDamage; }

	UFUNCTION(BlueprintCallable)
	bool CanAttack() const
	{
		return bIsPlayerInAttackRange && !bIsAttacking;
	}

	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;

	void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser) override;

	//UPROPERTY(BlueprintAssignable)
	//FOnHitDelegate OnHitDelegate;

protected:
	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnDeath(AActor* DeathCauser) override;

	UFUNCTION(BlueprintCallable)
	void DamagePlayer(APlayerCharacter* Player);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* AttackTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPlayerInAttackRange = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDamage = 10.f;
	
private:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	const FName AttackNotifyName = FName("AttackTrigger");
};
