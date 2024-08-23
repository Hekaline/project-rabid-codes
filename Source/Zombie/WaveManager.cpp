// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "Kismet/GameplayStatics.h"

void UWaveManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
}

void UWaveManager::Deinitialize()
{
	Super::Deinitialize();

	
}

void UWaveManager::SpawnActor(TSubclassOf<AActor> ClassToSpawn, FVector& Pos)
{
	const FTransform SpawnTransform = FTransform(
		FRotator::ZeroRotator, Pos, FVector::Zero());
	GetWorld()->SpawnActor(ClassToSpawn, &SpawnTransform);
}

