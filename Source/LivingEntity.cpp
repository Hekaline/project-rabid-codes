// Fill out your copyright notice in the Description page of Project Settings.


#include "LivingEntity.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALivingEntity::ALivingEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALivingEntity::BeginPlay()
{
	Super::BeginPlay();

	// 캐릭터 움직임 컴포넌트 걷기 속도
	// 뛰기 속도가 따로 없어서 MaxWalkSpeed를 조정하면 된다.
	SetWalkSpeed(WalkSpeed);

	// OnTakeAnyDamage를 호출 시 AddDynamic 두 번째 파라미터(콜백)가 호출됨
	// UGamePlayStatics::ApplyDamage(...)에서도 OnTakeAnyDamage가 호출됨
	OnTakeAnyDamage.AddDynamic(this, &ALivingEntity::OnTakeDamage);
}

// Called every frame
void ALivingEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALivingEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ALivingEntity::BeginHeal_Implementation(float Amount, int32 Numbers, float Delay)
{
	FTimerHandle HealTimerHandle;
	
	GetWorldTimerManager().SetTimer(
		HealTimerHandle,
		FTimerDelegate::CreateLambda([&]{ApplyHeal(Amount, Numbers, Delay, HealTimerHandle);}),
		Delay,
		false);
}

void ALivingEntity::ApplyHeal(float Amount, int Numbers, float Delay, FTimerHandle& Handle)
{
	if (Numbers <= 0)
	{
		GetWorldTimerManager().ClearTimer(Handle);
		HealTimerHandles.Remove(Handle);
	}

	// 재귀적으로 다음 ApplyHeal을 Delay 시간 뒤에 호출
	GetWorldTimerManager().SetTimer(
		Handle,
		FTimerDelegate::CreateLambda([&] {ApplyHeal(Amount, Numbers - 1, Delay, Handle);}),
		Delay,
		false
	);

	// 실제 체력 회복
	ApplyHeal(Amount);
}

void ALivingEntity::CancelAllHeals()
{
	for (auto Iter = HealTimerHandles.CreateIterator(); Iter; ++Iter)
	{
		GetWorldTimerManager().ClearTimer(*Iter);
		HealTimerHandles.Remove(*Iter);
	}
}

void ALivingEntity::ApplyHeal(float Amount)
{
	CurrHealth = FMath::Min(CurrHealth + Amount, MaxHealth);
}

void ALivingEntity::ApplyDamage(float Amount)
{
	CurrHealth = FMath::Max(CurrHealth - Amount, 0);
}

void ALivingEntity::OnDeath(AActor* DeathCauser)
{
	if (DeathCauser != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is dead by %s"), *GetName(), *DeathCauser->GetName())
	} else
	{
		// Dead by unknown
	}
}

void ALivingEntity::OnTakeDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (DamageCauser == nullptr)
	{
		DamageCauser = this;
	}
	
	ApplyDamage(Damage);

	if (CurrHealth <= 0.f)
	{
		OnDeath(DamageCauser);
	}
}
