// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ItemDataAsset.h"
//#include "Project_Rabid_5_3/Firearm.h"
#include "FirearmDataAsset.generated.h"

/**
 * 
 */


// enum class EFirearmType;

UCLASS()
class PROJECT_RABID_5_3_API UFirearmDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:
	// 주무기인지 보조무기인지 옵션 
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//EFirearmType Type = EFirearmType::Primary;
	
	// 한 번 명중할 때마다 주는 데미지 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.f;

	// Rounds Per Minute. 1분에 발사하는 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rpm = 0.f;

	// 총기의 정확성. 단위는 Minute Of Arc(MOA).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Accuracy = 0.f;

	// 적을 관통하는 횟수. 0이면 적이 맞는 즉시 총알이 파괴된다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PenetrateCount = 0;

	// 최대 여분 총알 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxExtraAmmo = 120;

	// 탄창 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagSize = 30;

	// 장전에 걸리는 시간(초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime = 3.f;

	// 약실에 총알이 들어갈 수 있는가?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsClosedBolt = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ReloadSound;
};
