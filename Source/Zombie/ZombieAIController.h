// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RABID_5_3_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

	AZombieAIController();
	
public:
	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
};
