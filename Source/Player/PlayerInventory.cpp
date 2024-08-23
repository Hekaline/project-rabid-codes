// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"
#include "../Item/EquipableItem.h"
#include "../Item/Firearm/Firearm.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ItemArr.SetNum(MaxItemIdx);
	ItemArr.Init(nullptr, MaxItemIdx);
	InitBeginningItems();
}

void UPlayerInventory::InitBeginningItems()
{
	for (int i = 0; i < BeginningItemClasses.Num(); i++)
	{
		if (i >= MaxItemIdx)
		{
			// out of index
			UE_LOG(LogTemp, Warning, TEXT("BeginningItemClasses array is larger than MaxItemIdx!"));
			return;
		}
		
		auto ItemClass = BeginningItemClasses[i];
		// ItemArr.Push(Cast<AEquipableItem>(GetWorld()->SpawnActor(ItemClass)));
		ItemArr[i] = Cast<AEquipableItem>(GetWorld()->SpawnActor(ItemClass));
		ItemArr[i]->OnUnequip();
	}
}

// Called every frame
void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AFirearm* UPlayerInventory::GetPrimaryWeapon() const
{
	return Cast<AFirearm>(GetItem(0));
}

AFirearm* UPlayerInventory::GetSecondaryWeapon() const
{
	return Cast<AFirearm>(GetItem(1));
}

void UPlayerInventory::SetPrimaryWeapon(AFirearm* WeaponToChange)
{
	SetItem(WeaponToChange, 0);
}

void UPlayerInventory::SetSecondaryWeapon(AFirearm* WeaponToChange)
{
	SetItem(WeaponToChange, 1);
}

AEquipableItem* UPlayerInventory::GetItem(int Index) const
{
	if (Index >= ItemArr.Num() || Index < 0)
	{
		// Index out of range
		UE_LOG(LogTemp, Warning, TEXT("UPlayerInventory::GetItem - Index Out Of Range!"));
		return nullptr;
	}
	
	// 기타 아이템 가져오기
	if (ItemArr[Index] != nullptr)
	{
		return ItemArr[Index];
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Could not get an item from inventory."));
	return nullptr;
}

void UPlayerInventory::SetItem(AEquipableItem* ItemToChange, int Index)
{
	if (Index >= ItemArr.Num())
	{
		// Index out of range
		UE_LOG(LogTemp, Warning, TEXT("Index Out Of Range!"));
		return;
	}
	
	if (ItemToChange != nullptr)
	{
		ItemArr[Index] = ItemToChange;
	}

	UE_LOG(LogTemp, Warning, TEXT("Item to change is nullptr!"));
}
