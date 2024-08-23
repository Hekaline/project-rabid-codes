// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Rabid_5_3/Zombie/ZombieCharacter.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComp);
	BulletEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Bullet Effect"));
	BulletEffect->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateLambda([this]
		{
			Destroy();
		}),
		5.f,
		false
	);
}

void ABullet::InitBullet(const int32 _PenetrateCnt, const float _Damage)
{
	PenetrateCnt = _PenetrateCnt;
	Damage = _Damage;
}

void ABullet::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// is zombie hit?
	if (AZombieCharacter* Zombie = Cast<AZombieCharacter>(OtherActor))
	{
		UClass* DamageTypeClass = UDamageType::StaticClass();
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		
		UGameplayStatics::ApplyDamage(
			OtherActor, Damage, PlayerCharacter->Controller, PlayerCharacter, DamageTypeClass);

		PenetrateCnt -= 1;
		if (PenetrateCnt < 0)
		{
			Destroy();
		}
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

