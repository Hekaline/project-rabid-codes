// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "EquipableItem.generated.h"

UCLASS()

class PROJECT_RABID_5_3_API AEquipableItem
	: public AItemBase
{
	GENERATED_BODY()

	

public:
	AEquipableItem();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = Event)
	void OnEquip();

	UFUNCTION(BlueprintNativeEvent, Category = Event)
	void OnUnequip();

	UFUNCTION(BlueprintNativeEvent, Category = Event)
	void OnUse();

protected:

private:

	
public:
protected:
private:
};
