// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MakeZombieDead.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RABID_5_3_API UBTTask_MakeZombieDead : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MakeZombieDead();

protected:
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;
};
