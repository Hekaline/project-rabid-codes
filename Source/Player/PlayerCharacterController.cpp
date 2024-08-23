// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	BindActions();
}

void APlayerCharacterController::BindActions()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem == nullptr || IMC_Player  == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Subsystem or IMC_Player is null"));
		
		return;
	}

	Subsystem->AddMappingContext(IMC_Player, 0);
	UE_LOG(LogTemp, Warning, TEXT("init Subsystem completed in BeginPlay"));

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComp is null!"));
		return;
	}

	// if (IA_Look)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_Look,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::Look
	// 	);
	// }
	//
	// if (IA_BeginSprint)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_BeginSprint,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::BeginSprint
	// 	);
	// }
	//
	// if (IA_EndSprint)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_EndSprint,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::EndSprint
	// 	);
	// }
	//
	// if (IA_Move)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_Move,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::Move
	// 	);
	// }
	//
	// if (IA_Jump)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_Jump,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::Jump
	// 	);
	// }

	// if (IA_Fire)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_Fire,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::TryFire
	// 	);
	// }
	//
	// if (IA_Aim)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_Aim,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::Aim
	// 	);
	// }
	//
	// if (IA_Reload)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_Reload,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::Reload
	// 	);
	// }
	//
	// if (IA_Interact)
	// {
	// 	EnhancedInputComp->BindAction(
	// 		IA_Interact,
	// 		ETriggerEvent::Triggered,
	// 		this,
	// 		&APlayerCharacterController::Interact
	// 	);
	// }

	
}

void APlayerCharacterController::Look(const FInputActionValue& Val)
{
	FVector2d ValAsVector = Val.Get<FVector2d>();

	GetPawn()->AddControllerYawInput(ValAsVector.X);
	GetPawn()->AddControllerPitchInput(ValAsVector.Y);
}

// 달리기 토글
void APlayerCharacterController::BeginSprint(const FInputActionValue& Val)
{
	if (GetAPlayerCharacter()->CanSprint())
		ToggleSprint(true);
}

void APlayerCharacterController::EndSprint(const FInputActionValue& Val)
{
	ToggleSprint(false);
}

void APlayerCharacterController::ToggleSprint(bool bShouldSprint)
{
	float ApplySpeed = 0.f;
	bool& bIsRunning = GetAPlayerCharacter()->bIsSprinting;
	UCharacterMovementComponent* MovementComp = GetCharacter()->GetCharacterMovement();
	
	if (!MovementComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find Movement Component!"));
	
		return;
	}
	if (bShouldSprint && GetAPlayerCharacter()->CanSprint())
	{
		// 걷기 -> 달리기
		ApplySpeed = GetAPlayerCharacter()->GetSprintSpeed();
		bIsRunning = true;
	}
	else
	{
		// 달리기 -> 걷기
		ApplySpeed = GetAPlayerCharacter()->GetWalkSpeed();
		bIsRunning = false;
	}
	
	MovementComp->MaxWalkSpeed = ApplySpeed;
}

void APlayerCharacterController::Move(const FInputActionValue& Val)
{
	if (!GetAPlayerCharacter()->CanSprint())
	{
		ToggleSprint(false);
	}
	FVector2D ValAsVec2 = Val.Get<FVector2D>();

	// 속도는 ToggleSprint에서 조정된다.
	GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), ValAsVec2.X);
	GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), ValAsVec2.Y);
}

void APlayerCharacterController::Jump(const FInputActionValue& Val)
{
	GetCharacter()->Jump();
}