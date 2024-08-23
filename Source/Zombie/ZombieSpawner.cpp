// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSpawner.h"
#include "../Zombie/ZombieCharacter.h"

// Sets default values
AZombieSpawner::AZombieSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieSpawner::SpawnZombie(float SpawnRadius)
{
	if (ZombieClassToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Zombie Class to Spawn is nullptr!"));
		return;
	}
	
	SpawnRadius = FMath::Max(0, SpawnRadius);
	
	FVector SpawnLocation;
	SpawnLocation.X = FMath::FRandRange(0, SpawnRadius);
	SpawnLocation.Y = FMath::FRandRange(0, SpawnRadius);
	SpawnLocation.Z = 0.f;

	SpawnLocation += GetActorLocation();
	
	AZombieCharacter* Zombie = Cast<AZombieCharacter>(GetWorld()->SpawnActor(ZombieClassToSpawn, &SpawnLocation));
	Zombie->SpawnDefaultController();
}