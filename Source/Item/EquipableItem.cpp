// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipableItem.h"

AEquipableItem::AEquipableItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEquipableItem::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipableItem::OnEquip_Implementation()
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
}

void AEquipableItem::OnUnequip_Implementation()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void AEquipableItem::OnUse_Implementation()
{
	// UE_LOG(LogTemp, Warning, TEXT("Please Implement OnUse in Blueprint!")); 
}
