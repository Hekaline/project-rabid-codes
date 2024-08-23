// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "Player/PlayerCharacter.h"

UInteractionComponent::UInteractionComponent()
{
	SphereRadius = 32.f;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::OnInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("OnInteract is not implemented!"));
}
