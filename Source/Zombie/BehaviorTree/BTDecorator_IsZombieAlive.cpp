// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsZombieAlive.h"
#include "AIController.h"
#include "../ZombieCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

UBTDecorator_IsZombieAlive::UBTDecorator_IsZombieAlive()
{
	NodeName = "Is Zombie Alive?";
	bTickIntervals = true;
	bAllowAbortNone = true;
	bAllowAbortChildNodes = true;
	bAllowAbortLowerPri = true;
}


bool UBTDecorator_IsZombieAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	if (AZombieCharacter* Zombie = Cast<AZombieCharacter>(
		OwnerComp.GetAIOwner()->GetPawn()))
	{
		return !Zombie->IsDead();
	}
	
	return false;
}
