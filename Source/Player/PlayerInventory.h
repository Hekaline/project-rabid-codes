// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "../Item/Firearm/Firearm.h"
#include "PlayerInventory.generated.h"


class AEquipableItem;
class AFirearm;
class UInputAction;
class UInputMappingContext;
class AItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_RABID_5_3_API UPlayerInventory : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InitBeginningItems();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 주무기를 반환합니다.
	UFUNCTION(BlueprintCallable)
	AFirearm* GetPrimaryWeapon() const;

	// 보조무기를 반환합니다.
	UFUNCTION(BlueprintCallable)
	AFirearm* GetSecondaryWeapon() const;

	// 주무기를 교체합니다.
	UFUNCTION(BlueprintCallable)
	void SetPrimaryWeapon(AFirearm* WeaponToChange);

	// 보조무기를 교체합니다.
	UFUNCTION(BlueprintCallable)
	void SetSecondaryWeapon(AFirearm* WeaponToChange);
	
	// Index 번째의 아이템을 가져옵니다.
	UFUNCTION(BlueprintCallable)
	AEquipableItem* GetItem(int Index) const;

	// Index 번째의 아이템을 Item으로 바꿉니다.
	UFUNCTION(BlueprintCallable)
	void SetItem(AEquipableItem* ItemToChange, int Index);


public:
	// // 인벤토리를 위한 InputMappingContext
	// UPROPERTY(EditAnywhere, Category = Input)
	// UInputMappingContext* IMC_Inventory = nullptr;
	//
	// // 번호가 하나 낮은 아이템 꺼내기(주로 마우스 휠 업)
	// UPROPERTY(EditAnywhere, Category = Input)
	// UInputAction* IA_Negative = nullptr;
	//
	// // 번호가 하나 높은 아이템 꺼내기(주로 마우스 휠 다운)
	// UPROPERTY(EditAnywhere, Category = Input)
	// UInputAction* IA_Positive = nullptr;
	
	
private:
	UPROPERTY(EditAnywhere, Category = Item)
	TArray<TSubclassOf<AEquipableItem>> BeginningItemClasses;

	UPROPERTY(VisibleAnywhere, Category = Item)
	TArray<AEquipableItem*> ItemArr;

	UPROPERTY(EditAnywhere, Category = Item)
	int32 MaxItemIdx = 4;
};
