// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Rabid_5_3/Player/PlayerCharacter.h"

AZombieCharacter::AZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AttackTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Attack Trigger"));
	AttackTrigger->SetupAttachment(RootComponent);
	AttackTrigger->SetCollisionProfileName(FName("OverlapAll"));
}

void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AttackTrigger->OnComponentBeginOverlap.AddDynamic(
		this, &AZombieCharacter::OnTriggerBeginOverlap); // canAttack = true;
	
	AttackTrigger->OnComponentEndOverlap.AddDynamic(
		this, &AZombieCharacter::OnTriggerEndOverlap); // canAttack = false;
}

void AZombieCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsPlayerInAttackRange)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (!AnimInstance)
		{
			bIsAttacking = false;
			return;
		}

		if (AnimInstance->IsAnyMontagePlaying())
		{
			bIsAttacking = true;

			// AttackNotifyName을 가진 노티파이가 활성화되었는가?
			bool bAttackNotifyTriggered =
				AnimInstance->
				WasAnimNotifyNameTriggeredInAnyState(
					FName(AttackNotifyName));

			// 공격 트리거(노티파이) 발동 시점인가?
			if (bAttackNotifyTriggered)
			{
				// 오버랩된(맞은) 액터
				TArray<AActor*> HitActors;

				// 오버랩된 플레이어 캐릭터를 AActor*로써 구하기
				AttackTrigger->GetOverlappingActors(
					OUT HitActors, APlayerCharacter::StaticClass());
				
				for (AActor* HitActor : HitActors)
				{
					// 액터가 플레이어인가?
					// AActor* -> APlayerCharacter*
					APlayerCharacter* HitPlayer = Cast<APlayerCharacter>(HitActor);
					if (HitPlayer == nullptr) continue;

					// 변환한 플레이어 데미지
					DamagePlayer(HitPlayer);
				}
			}
			return;
		}

		bIsAttacking = false;
	}
}

void AZombieCharacter::DamagePlayer(APlayerCharacter* Player)
{
	if (Player == nullptr)
	{
		return;
	}

	UGameplayStatics::ApplyDamage(
		Player,
		AttackDamage,
		GetController(),
		this,
		UDamageType::StaticClass());
}

void AZombieCharacter::OnTakeDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	Super::OnTakeDamage(
		DamagedActor,
		Damage,
		DamageType,
		InstigatedBy,
		DamageCauser);

	// if (OnHitDelegate.IsBound())
	// {
	// 	OnHitDelegate.Broadcast();
	// }
}


void AZombieCharacter::OnDeath(AActor* DeathCauser)
{
	Super::OnDeath(DeathCauser);

	bIsDead = true;

	// 콜리전 없앰
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 공격 애니메이션 몽타주 중지
	GetMesh()->GetAnimInstance()->StopAllMontages(0.1f);

	// 죽을 때 회전 방지
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	// Destroy zombie after 3 seconds
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateLambda([this]
		{
			Destroy();
		}),
		3.f,
		false
	);
}

void AZombieCharacter::OnTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// true이면 공격 애니메이션 몽타주를 AnimBP에서 활성화
		bIsPlayerInAttackRange = true;
	}
}

void AZombieCharacter::OnTriggerEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		bIsPlayerInAttackRange = false;
	}
}
