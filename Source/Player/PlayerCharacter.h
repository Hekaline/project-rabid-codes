// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "../LivingEntity.h"
#include "Ability.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

class UCameraComponent;
class UUserWidget;
class AEquipableItem;
class UPlayerInventory;
class AItemBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbility);
UCLASS(Blueprintable, BlueprintType, meta=(IsBlueprintBase="true", BlueprintSpawnableComponent="true"))
class PROJECT_RABID_5_3_API APlayerCharacter : public ALivingEntity
{
	GENERATED_BODY()
	APlayerCharacter();

	friend class APlayerCharacterController;
	
	///////////////// functions begins ///////////////////
public:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// 아이템(ItemToAttach)을 BoneNameToAttachItem에 부착한다.
	UFUNCTION(BlueprintCallable)
	bool AttachItemToHand(AEquipableItem* ItemToAttach);
	
	// 특수능력을 사용할 수 있는지 체크한다.
	// 블루프린트에서 이것을 오버라이드하는 것이 좋다.
	UFUNCTION(BlueprintNativeEvent)
	bool CanUseAbility();

	UFUNCTION(BlueprintCallable)
	bool CanSprint() const;

	UFUNCTION(BlueprintCallable)
	bool IsSprinting() const { return bIsSprinting; }

	UFUNCTION(BlueprintCallable)
	void ToggleSprint(bool bShouldSprint);
	
	// CanUseAbility()를 가지고 특수능력 사용을 시도한다.
	UFUNCTION(Blueprintcallable)
	bool TryUsingAbility();

	// SprintSpeed의 Getter
	UFUNCTION(BlueprintCallable)
	float GetSprintSpeed() const { return SprintSpeed; }

	UFUNCTION(BlueprintCallable)
	void SetSprintSpeed(float Value)
	{
		Value = FMath::Max(0.f, Value);
		SprintSpeed = Value;
	}
	
	// CurrentSpeed의  Getter
	UFUNCTION(BlueprintCallable)
	float GetCurrentSpeed() const { return GetVelocity().Length(); }

	// bIsRunning의 Getter
	UFUNCTION(BlueprintCallable)
	bool IsRunning() const { return bIsSprinting; }

	UFUNCTION(BlueprintCallable)
	bool IsTryingToFire() const { return bIsTryingToFire; }

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetHudWidget() const { return HudWidget; }

protected:
	// 특수능력 사용. 캐릭터마다 다릅니다.
	UFUNCTION(BlueprintNativeEvent)
	void UseAbility();

	UFUNCTION(BlueprintCallable)
	void EquipPrimaryWeapon(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EquipSecondaryWeapon(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EquipItem1(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EquipItem2(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EquipItemAt(int Index);

	UFUNCTION(BlueprintCallable)
	void TryFire(const FInputActionValue& Val);

	UFUNCTION(BlueprintCallable)
	void EndFire(const FInputActionValue& Val);

	UFUNCTION(BlueprintCallable)
	void Reload(const FInputActionValue& Val);

	UFUNCTION(BlueprintCallable)
	void Aim(const FInputActionValue& Val);

	UFUNCTION(BlueprintCallable)
	void Interact(const FInputActionValue& Val);
	
private:
	void Look(const FInputActionValue& Val);
	void BeginSprint(const FInputActionValue& Val);
	void EndSprint(const FInputActionValue& Val);
	void Move(const FInputActionValue& Val);
	void PerformJump(const FInputActionValue& Val);

	////////////////// functions ends //////////////////////

	
	////////////////// properties begins ////////////////////
public:
	
	
protected:
	UPROPERTY(EditAnywhere)
	FName BoneNameToAttachItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEquipableItem* ItemOnHand = nullptr;

	UPROPERTY(EditAnywhere)
	UPlayerInventory* PlayerInventory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HudWidgetClass;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* HudWidget;
	
	// 주위를 둘러보기 위한 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Look;

	// 달리기 시작 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_BeginSprint;
	
	// 달리기 중지 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_EndSprint;

	// (주로) WASD로 움직이기 위한 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Move;

	// 점프를 위한 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Jump;

	// 주무기 교체
	UPROPERTY(EditAnywhere)
	UInputAction* EquipPrimaryAction;

	// 보조무기 교체
	UPROPERTY(EditAnywhere)
	UInputAction* EquipSecondaryAction;

	// 아이템 1 장착
	UPROPERTY(EditAnywhere)
	UInputAction* EquipItem1Action;

	// 아이템 2 장착
	UPROPERTY(EditAnywhere)
	UInputAction* EquipItem2Action;

	// 발사 액션
	UPROPERTY(EditAnywhere)
	UInputAction* FireAction;

	// 재장전 액션
	UPROPERTY(EditAnywhere)
	UInputAction* ReloadAction;

	// 조준 액션
	UPROPERTY(EditAnywhere)
	UInputAction* AimAction;

	// 상호작용 액션
	UPROPERTY(EditAnywhere)
	UInputAction* InteractAction;

	// 재장전 애니메이션 몽타주
	UPROPERTY(EditAnywhere)
	UAnimMontage* ReloadMontage;

	// 발사 애니메이션 몽타주
	UPROPERTY(EditAnywhere)
	UAnimMontage* FireMontage;
	
private:
	UPROPERTY(EditAnywhere)
	float SprintSpeed = 800.f;
	
	bool bIsSprinting = false;

	UPROPERTY()
	bool bIsTryingToFire = false;

	UPROPERTY()
	int CurrInventoryIndex = -1;

	////////////////// properties ends ////////////////////
};
