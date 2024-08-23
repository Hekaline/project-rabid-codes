// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"

#include "ZombieCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AZombieAIController::AZombieAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	// 행동 트리 실행 시도
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIBehavior is nullptr!"));
	}

	GetBlackboardComponent()->SetValueAsObject("PlayerActor",
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AZombieAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AZombieCharacter* Zombie = Cast<AZombieCharacter>(GetCharacter()))
	{
		if (Zombie->IsDead())
		{
			
		}
	}
	// 움직임이 부드럽기는 하지만, 렉 유발 가능성 있음
	// 또한 트리가 원활하게 실행되지 않을 수도 있음
	// MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}