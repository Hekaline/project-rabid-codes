// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RABID_5_3_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// 유저가 알아보기 쉬운 아이템의 이름 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString("NoName");
	
	// 아이템의 2D 썸네일 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail = nullptr;

	// 아이템의 무게 (gram) 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 0.f;

	// 아이템 설명 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description = FText::FromString("description");
};
