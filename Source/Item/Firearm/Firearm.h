// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EquipableItem.h"
#include "FirearmDataAsset.h"
#include "Firearm.generated.h"


class ABullet;
class UFirearmDataAsset;

/// <summary>
/// <para> 무기 종류 </para>
/// </summary>
UENUM(BlueprintType)
enum class EFirearmType : uint8
{
	// 주무기
	Primary UMETA(DisplayName = "Primary"),

	// 보조무기
	Secondary UMETA(DisplayName = "Secondary"),
};

UCLASS()
class PROJECT_RABID_5_3_API AFirearm : public AEquipableItem
{
	GENERATED_BODY()

	//////////////////// FUNCTION BEGINS //////////////////////
	
public:
	AFirearm();
	virtual void BeginPlay() override;

	// AEquipableItem의 Data를 UFirearmDataAsset으로 변환하여 얻어온다.
	UFUNCTION(BlueprintCallable)
	UFirearmDataAsset* GetFirearmData() const
	{ return Cast<UFirearmDataAsset>(Data); }

	UFUNCTION(BlueprintCallable)
	bool IsReloading() const
	{ return bIsReloading; }

	UFUNCTION(BlueprintCallable)
	bool IsFiring() const
	{
		return GetWorldTimerManager().IsTimerActive(FireDelayHandle);
	}

	// RPM을 지연 시간으로 변환한다.
	UFUNCTION(BlueprintCallable)
	float RpmToDelayTime() { return 60.f / CurrentFirearmData->Rpm; }

	// 발사하려고 시도한다. 발사할 수 있다면 총알을 발사한다. 
	UFUNCTION(BlueprintCallable)
	bool TryFire();

	// 발사할 수 있는지 여부를 반환한다.
	UFUNCTION(BlueprintCallable)
	bool CanFire() const;

	// 장전하려고 시도한다. 장전할 수 있다면 장전을 실행한다.
	UFUNCTION(BlueprintCallable)
	bool TryReload();

	UFUNCTION(BlueprintCallable)
	void CancelReload();

	// 장전할 수 있는지 여부를 반환한다.
	UFUNCTION(BlueprintCallable)
	bool CanReload() const;

protected:
	// (TryFire 등을 거쳐) 실제 발사를 한다.
	UFUNCTION(BlueprintNativeEvent)
	void Fire();

	UFUNCTION()
	ABullet* SpawnBullet();
	
	// 발사 딜레이를 설정한다.
	// 딜레이 시간 동안 총을 발사할 수 없다.
	UFUNCTION()
	void SetFireDelay();

	// 재장전 딜레이를 설정한다.
	// 딜레이 시간 동안 총을 발사할 수 없다.
	UFUNCTION()
	void SetReloadDelay();
	
	// (TryReload 등을 거쳐) 실제 장전을 한다.
	UFUNCTION(BlueprintNativeEvent)
	void Reload();

	UFUNCTION()
	void OnUnequip_Implementation() override;
	
	// EquipableItem(상위 클래스)으로서 TryFire을 호출할 수 있음.
	UFUNCTION()
	void OnUse_Implementation() override { TryFire(); }

private:
	//////////////////// FUNCTION ENDS //////////////////////
	
	
	/////////////////////// PROPERTY BEGINS //////////////////////
	
public:
	UPROPERTY()
	FName BoneNameToAttach;
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> BulletClassToSpawn;

	
private:
	// 발사 딜레이를 관리하는 핸들 
	UPROPERTY()
	FTimerHandle FireDelayHandle;

	// 재장전 딜레이를 관리하는 핸들
	UPROPERTY()
	FTimerHandle ReloadDelayHandle;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UFirearmDataAsset* CurrentFirearmData;

	// 현재 여분 총알 수
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	int32 CurrExtraAmmo = 120;

	// 현재 탄창에 들어있는 총알 수
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	int32 CurrMagAmmo = 30;
	
	// 발사 지연 여부. SetFireDelay()에서 조작됨.
	UPROPERTY()
	bool bFireDelayed = false;

	// 재장전 지연 여부. SetReloadDelay()에서 조작됨.
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bIsReloading = false;
	

	UPROPERTY()
	UAudioComponent* ReloadSoundComp;
	
	/////////////////////// PROPERTY ENDS //////////////////////
};
