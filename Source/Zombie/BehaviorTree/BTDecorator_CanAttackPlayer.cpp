// Fill out your copyright notice in the Description page of Project Settings.
#include "BTDecorator_CanAttackPlayer.h"
#include "AIController.h"
#include "../ZombieCharacter.h"

UBTDecorator_CanAttackPlayer::UBTDecorator_CanAttackPlayer()
{
	NodeName = "Can Attack Player?";
	// bTickIntervals = true;
	bAllowAbortNone = true;
	bAllowAbortChildNodes = true;
	bAllowAbortLowerPri = true;
}

bool UBTDecorator_CanAttackPlayer::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AZombieCharacter* Zombie = Cast<AZombieCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie == nullptr)
	{
		return false;
	}

	return Zombie->CanAttack();
}
