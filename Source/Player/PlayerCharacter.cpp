// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "../Item/ItemBase.h"
#include "PlayerInventory.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "../Item/EquipableItem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacterController.h"
#include "../Item/Firearm/Firearm.h"
#define NAMEOF(s) FString(#s)


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Inventory System
	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>("Inventory");

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Set Position of the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Attach Camera to Player Mesh
	GetMesh()->SetupAttachment(CameraComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HudWidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HudWidgetClass is null!"));
		return;
	}
	
	// HudWidgetClass를 가지고 HudWidget 생성
	HudWidget = CreateWidget(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	if (HudWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HudWidget is null!"));
		return;
	}

	FTimerDelegate EquipPrimaryDel = FTimerDelegate::CreateLambda(
		[this]
		{
			EquipItemAt(0);
		});

	// 인벤토리에서 아이템이 생성되지 않았을 수도 있으니 잠깐 기다린다
	GetWorldTimerManager().SetTimerForNextTick(EquipPrimaryDel);

	UE_LOG(LogTemp, Warning, TEXT("Init success in Player Character"));
}

bool APlayerCharacter::CanSprint() const
{
	AFirearm* FirearmOnHand = Cast<AFirearm>(ItemOnHand);

	if (FirearmOnHand)
	{
		if (FirearmOnHand->IsReloading() || FirearmOnHand->IsFiring())
		{
			return false;
		}
	}

	// 총을 들고 있지 않다면 뛸 수 있게 설정함
	return true;
}

// InputAction 초기화
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Look)
		{
			EInputComp->BindAction(
				IA_Look,
				ETriggerEvent::Triggered,
				this,
				&APlayerCharacter::Look
			);
		}

		if (IA_BeginSprint)
		{
			EInputComp->BindAction(
				IA_BeginSprint,
				ETriggerEvent::Triggered,
				this,
				&APlayerCharacter::BeginSprint
			);
		}

		if (IA_EndSprint)
		{
			EInputComp->BindAction(
				IA_EndSprint,
				ETriggerEvent::Triggered,
				this,
				&APlayerCharacter::EndSprint
			);
		}

		if (IA_Move)
		{
			EInputComp->BindAction(
				IA_Move,
				ETriggerEvent::Triggered,
				this,
				&APlayerCharacter::Move
			);
		}

		if (IA_Jump)
		{
			EInputComp->BindAction(
				IA_Jump,
				ETriggerEvent::Triggered,
				this,
				&APlayerCharacter::PerformJump
			);
		}
		
		// Equip Primary Weapon
		EInputComp->BindAction(
			EquipPrimaryAction,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::EquipPrimaryWeapon);

		// Equip Secondary Weapon
		EInputComp->BindAction(
			EquipSecondaryAction,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::EquipSecondaryWeapon);

		// Equip Item1
		EInputComp->BindAction(
			EquipItem1Action,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::EquipItem1);

		// Equip Item2
		EInputComp->BindAction(
			EquipItem2Action,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::EquipItem2);

		EInputComp->BindAction(
			FireAction,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::TryFire);

		EInputComp->BindAction(
			ReloadAction,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::Reload);

		EInputComp->BindAction(
			AimAction,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::Aim);

		EInputComp->BindAction(
			InteractAction,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::Interact);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Val)
{
	FVector2d ValAsVector = Val.Get<FVector2d>();

	AddControllerYawInput(ValAsVector.X);
	AddControllerPitchInput(ValAsVector.Y);
}

// 달리기 토글
void APlayerCharacter::BeginSprint(const FInputActionValue& Val)
{
	if (CanSprint())
	{
		ToggleSprint(true);
	}
}

void APlayerCharacter::EndSprint(const FInputActionValue& Val)
{
	ToggleSprint(false);
}

void APlayerCharacter::ToggleSprint(bool bShouldSprint)
{
	float ApplySpeed = 0.f;
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	
	if (!MovementComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find Movement Component!"));
	
		return;
	}
	if (bShouldSprint && CanSprint())
	{
		// 걷기 -> 달리기
		ApplySpeed = GetSprintSpeed();
		bIsSprinting = true;
	}
	else
	{
		// 달리기 -> 걷기
		ApplySpeed = GetWalkSpeed();
		bIsSprinting = false;
	}
	
	MovementComp->MaxWalkSpeed = ApplySpeed;
}

void APlayerCharacter::Move(const FInputActionValue& Val)
{
	if (!CanSprint())
	{
		ToggleSprint(false);
	}
	FVector2D ValAsVec2 = Val.Get<FVector2D>();

	// 속도는 ToggleSprint에서 조정된다.
	AddMovementInput(GetActorRightVector(), ValAsVec2.X);
	AddMovementInput(GetActorForwardVector(), ValAsVec2.Y);
}

void APlayerCharacter::PerformJump(const FInputActionValue& Val)
{
	Jump();
}

void APlayerCharacter::EquipPrimaryWeapon(const FInputActionValue& Value)
{
	EquipItemAt(0);
}

void APlayerCharacter::EquipSecondaryWeapon(const FInputActionValue& Value)
{
	EquipItemAt(1);
}

void APlayerCharacter::EquipItem1(const FInputActionValue& Value)
{
	EquipItemAt(2);
}

void APlayerCharacter::EquipItem2(const FInputActionValue& Value)
{
	EquipItemAt(3);
}

void APlayerCharacter::EquipItemAt(int Index)
{
	// 이미 장착하고 있으면 다시 장착할 필요 없음
	// Index Out Of Range는 UPlayerInventory::GetItem()에서 체크
	if (CurrInventoryIndex == Index) return;

	CurrInventoryIndex = Index;
	TObjectPtr<AEquipableItem> Item = PlayerInventory->GetItem(Index);

	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get Item at %d"), Index);
		return;
	}
	
	AttachItemToHand(Item);
}

// [함수이름]_Implementation: 함수가 BlueprintNativeEvent일 때 자동 생성됨
// 블루프린트에서 함수를 override하지 않았을 시 이 함수가 실행됨
// 블루프린트에서 이 함수를 호출도 가능하다. (Super)
bool APlayerCharacter::CanUseAbility_Implementation()
{
	// 능력 사용 가능 여부 확인
	// 능력 사용이 가능한 조건이 각자 다르므로 블루프린트에서 설정
	UE_LOG(LogTemp, Warning, TEXT(
		"Didn't override CanUseAbility() in player character!"));

	return false;
}


bool APlayerCharacter::TryUsingAbility()
{
	if (!CanUseAbility())
	{
		return false;
	}
	
	UseAbility();
	return true;
}


void APlayerCharacter::UseAbility_Implementation()
{
	// 특수 능력이 각자 다르므로 블루프린트에서 구현
	
	UE_LOG(LogTemp, Warning, TEXT("UseAbility in PlayerCharacter is not implemented!"));
	return;
}

void APlayerCharacter::TryFire(const FInputActionValue& Val)
{
	bIsTryingToFire = true;
	if (auto Firearm = Cast<AFirearm>(ItemOnHand))
	{
		if (Firearm->TryFire() == false) return;

		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(FireMontage);
		}
		Cast<APlayerCharacterController>(GetController())->ToggleSprint(false);
	}
	else if (ItemOnHand != nullptr)
	{
		ItemOnHand->OnUse();
	}
}

void APlayerCharacter::EndFire(const FInputActionValue& Val)
{
	bIsTryingToFire = false;
}


void APlayerCharacter::Reload(const FInputActionValue& Val)
{
	if (auto Firearm = Cast<AFirearm>(ItemOnHand))
	{
		// 재장전 불가
		if (Firearm->TryReload() == false) return;

		// 재장전 애니메이션 실행
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(ReloadMontage);
		}
	}
}

void APlayerCharacter::Aim(const FInputActionValue& Val)
{
	
}

void APlayerCharacter::Interact(const FInputActionValue& Val)
{
	
}

bool APlayerCharacter::AttachItemToHand(AEquipableItem* ItemToAttach)
{
	// 부착 규칙
	const FAttachmentTransformRules AttachRule(
		EAttachmentRule::SnapToTarget,
		true);

	// 장착되어 있었던 아이템 Unequip
	if (ItemOnHand != nullptr)
	{
		ItemOnHand->OnUnequip();
	}
	
	// 연결이 잘 되었는지 여부
	bool bAttachedCompletely =
		ItemToAttach->AttachToComponent(GetMesh(), AttachRule, BoneNameToAttachItem);

	if (!bAttachedCompletely)
	{
		const FString ErrorMessage =
			"Item was not attached completely.\nPlease check " + NAMEOF(BoneNameToAttachItem);
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
	}

	ItemOnHand = ItemToAttach;
	ItemToAttach->OnEquip();
	
	return bAttachedCompletely;
}
