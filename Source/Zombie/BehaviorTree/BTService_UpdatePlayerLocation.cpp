// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	// 노드 이름
	NodeName = "Update Player Location";
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 플레이어 폰 Get 시도
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}

	// AI 사용자가 없는지 체크
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	// 선택된 키를, 가져온 플레이어 폰의 위치로 업데이트
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(
		GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
