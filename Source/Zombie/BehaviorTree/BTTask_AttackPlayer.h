// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackPlayer.generated.h"

class APlayerCharacter;
class AZombieCharacter;
/**
 * 
 */
UCLASS()
class PROJECT_RABID_5_3_API UBTTask_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_AttackPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds) override;
	
	//UPROPERTY()
	//AZombieCharacter* CurrZombie;

	UPROPERTY()
	bool bIsZombieAttacking = false;

	UPROPERTY()
	float AnimLength = -1;

	
};
