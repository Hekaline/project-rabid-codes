// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackPlayer.h"
#include "../ZombieCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer()
{
	NodeName = "Attack Player";
	bNotifyTick = true;
	bTickIntervals = true;
}
 
EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	// OwnerComp.GetBlackboardComponent()->GetValue<UAnimMontage>(GetSelectedBlackboardKey());
	
	AZombieCharacter* CurrZombie = Cast<AZombieCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
	
	if (CurrZombie == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find zombie in UBTTask_AttackPlayer"));
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OwnerComp.GetAIOwner()->GetPawn()->GetClass()->GetName())
		return EBTNodeResult::Failed;
	}
	
	UAnimInstance* AnimInstance = CurrZombie->GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AnimLength = AnimInstance->Montage_Play(CurrZombie->AttackMontage);
	UE_LOG(LogTemp, Warning, TEXT("%f"), AnimLength);
	return EBTNodeResult::InProgress;
}

void UBTTask_AttackPlayer::TickTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AnimLength -= DeltaSeconds;
	// UE_LOG(LogTemp, Warning, TEXT("TickTask: %f"), AnimLength);
	if (AnimLength <= 0)
	{
		// continue execution from this node
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
