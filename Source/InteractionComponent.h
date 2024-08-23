// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractionComponent.generated.h"
class APlayerCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, APlayerCharacter*, PlayerInInteraction);
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class PROJECT_RABID_5_3_API UInteractionComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnInteract();

protected:
	virtual void BeginPlay() override;
};
