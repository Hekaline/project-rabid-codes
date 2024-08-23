// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WaveManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RABID_5_3_API UWaveManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SpawnActor(TSubclassOf<AActor> ClassToSpawn, FVector& Pos);
};
