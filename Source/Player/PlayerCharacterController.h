// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

class APlayerCharacter;
class UInputAction;
class UInputMappingContext;
/**
 * ALivingEntity를 움직이기 위한 컨트롤러
 */
UCLASS()
class PROJECT_RABID_5_3_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ToggleSprint(bool bShouldSprint);

protected:
	virtual void BeginPlay() override;

private:
	void BindActions();

	void Look(const FInputActionValue& Val);
	void BeginSprint(const FInputActionValue& Val);
	void EndSprint(const FInputActionValue& Val);
	void Move(const FInputActionValue& Val);
	
	void Jump(const FInputActionValue& Val);
	// void TryFire(const FInputActionValue& Val);
	// void Reload(const FInputActionValue& Val);
	// void Aim(const FInputActionValue& Val);
	// void Interact(const FInputActionValue& Val);
	// void GetPrimaryFirearm(const FInputActionValue& Val);
	// void GetSecondaryFirearm(const FInputActionValue& Val);

	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetAPlayerCharacter() const
	{ return Cast<APlayerCharacter>(GetCharacter()); }

public:
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

	// 발사 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Fire;

	// 조준 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Aim;

	// 상호작용 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Interact;

	// 재장전 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Reload;

	// 주무기 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Primary;

	// 재장전 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Secondary;
	
	// 재장전 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Item;

protected:

private:
	// 인풋 매핑 컨텍스트
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* IMC_Player;
};
