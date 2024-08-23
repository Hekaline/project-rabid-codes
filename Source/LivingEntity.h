// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "LivingEntity.generated.h"

class UInputAction;
class UCharacterMovementComponent;

UCLASS()
class PROJECT_RABID_5_3_API ALivingEntity
	: public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALivingEntity();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 캐릭터 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	// CurrHealth의 Getter
	float GetCurrHealth() const { return CurrHealth; };

	// WalkSpeed의 Getter
	UFUNCTION(BlueprintCallable)
	float GetWalkSpeed() const { return WalkSpeed; }

	UFUNCTION(BlueprintCallable)
	void SetWalkSpeed(float Value)
	{
		Value = FMath::Max(0.f, Value);
		
		WalkSpeed = Value;
		GetCharacterMovement()->MaxWalkSpeed = Value;
	}

	// 회복 시작. ApplyHeal을 실행합니다.
	UFUNCTION(BlueprintNativeEvent)
	void BeginHeal(float Amount, int32 Numbers = 1, float Delay = 0);

	// 사망 시 실행되는 메서드
	UFUNCTION()
	virtual void OnDeath(AActor* DeathCauser = nullptr) override;

	// 데미지를 받을 때 실행되는 메서드
	UFUNCTION()
	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser) override; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// 실제 체력 회복 수행
	virtual void ApplyHeal(float Amount);

	// 데미지 작업 수행
	virtual void ApplyDamage(float Amount);
	
	// 수 차례 체력 회복 시 사용
	virtual void ApplyHeal(float Amount, int Numbers, float Delay, FTimerHandle& Handle);

	// 체력 회복 전체 취소
	virtual void CancelAllHeals();
	

/** Properties + get/setters **/
public:
	// 생명체 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	

protected:
	// 현재 체력
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float CurrHealth = 100.f;

	// 걷기 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float WalkSpeed = 500.f;

private:
	UPROPERTY()
	TSet<FTimerHandle> HealTimerHandles;
};
