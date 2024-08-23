// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MakeZombieDead.h"

#include "AIController.h"
#include "../ZombieCharacter.h"

UBTTask_MakeZombieDead::UBTTask_MakeZombieDead()
{
	
}

EBTNodeResult::Type UBTTask_MakeZombieDead::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AZombieCharacter* Zombie =
		Cast<AZombieCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Zombie == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Zombie is null in BTTask_MakeZombieDead!"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}

