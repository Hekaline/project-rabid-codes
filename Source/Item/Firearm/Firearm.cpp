// Firearm.cpp

#include "Firearm.h"

#include "Components/AudioComponent.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Rabid_5_3/Player/PlayerCharacter.h"

AFirearm::AFirearm()
{
	SetRootComponent(AppearanceMesh);
}


void AFirearm::BeginPlay()
{
	Super::BeginPlay();

	// 게임 시작 시 대입되는 원본 총기 데이터
	UFirearmDataAsset* FirearmDataTemp = GetFirearmData();
	
	if (FirearmDataTemp == nullptr)
		return;

	// 원본이 훼손되지 않도록 하는 깊은 복사
	// 나중에 총 업그레이드 등을 할 때 원본을 다루는 대신 FirearmData를 사용할 수 있다.
	CurrentFirearmData = DuplicateObject<UFirearmDataAsset>(FirearmDataTemp, this);
}


bool AFirearm::TryReload()
{
	if (CanReload())
	{
		Reload();
		return true;
	}
	
	return false;
}

bool AFirearm::CanReload() const
{
	bool bIsAmmoEnough = CurrExtraAmmo > 0;
	bool bHasLessAmmoThanMag;
	
	if (CurrentFirearmData->bIsClosedBolt)
	{
		bHasLessAmmoThanMag = CurrMagAmmo <= (CurrentFirearmData->MagSize);
	}
	else
	{
		bHasLessAmmoThanMag = CurrMagAmmo < (CurrentFirearmData->MagSize);
	}

	// 여분 총알이 충분하고, 현재 총에 장전된 탄이 꽉 차지 않았으며 장전하고 있지 않으면 true
	return bIsAmmoEnough && bHasLessAmmoThanMag && !bIsReloading;
}

void AFirearm::Reload_Implementation()
{
	SetReloadDelay();

	if (CurrentFirearmData->ReloadSound == nullptr) return;
	
	// 재장전 사운드 스폰
	UGameplayStatics::SpawnSoundAttached(CurrentFirearmData->ReloadSound, AppearanceMesh);
}

bool AFirearm::TryFire()
{
	// 발사할 수 있는지 검사하고 발사
	if (CanFire())
	{
		Fire();
		return true;
	}

	return false;
}

void AFirearm::Fire_Implementation()
{
	// 실제 발사 진행
	
	// 딜레이 true 후 총알 -1
	SetFireDelay();
	CurrMagAmmo -= 1;
	
	// 재장전 취소
	CancelReload();

	// 총알 스폰 후 초기화
	ABullet* Bullet = SpawnBullet();
	Bullet->InitBullet(CurrentFirearmData->PenetrateCount, CurrentFirearmData->Damage);

	if (CurrentFirearmData->FireSound == nullptr) return;

	// 발사 사운드 재생
	UGameplayStatics::SpawnSoundAtLocation(
		GetWorld(), CurrentFirearmData->FireSound, AppearanceMesh->GetComponentLocation());
}

ABullet* AFirearm::SpawnBullet()
{
	// 총알을 스폰하기 위한 클래스가 지정되지 않음
	if (BulletClassToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Bullet Class To Spawn is nullptr!"));
		return nullptr;
	}

	// 카메라를 이용한 발사 트랜스폼 조정
	APlayerCameraManager* CamManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	const FVector SpawnLocation = GetActorLocation() + CamManager->GetActorUpVector();
	const FRotator SpawnRotation = CamManager->GetCameraRotation();
	const FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, FVector::One());
	
	// 총알 스폰
	AActor* Bullet = GetWorld()->SpawnActor(BulletClassToSpawn.Get(), &SpawnTransform);
	return Cast<ABullet>(Bullet);
}



bool AFirearm::CanFire() const
{
	return !bFireDelayed && CurrMagAmmo > 0;
}


void AFirearm::SetFireDelay()
{
	// 다음 탄 발사까지 딜레이가 있음
	bFireDelayed = true;
	const FTimerDelegate Del = FTimerDelegate::CreateLambda([this]()->void
	{
		bFireDelayed = false;
	});
	
	// 딜레이를 false로 만드는 타이머 적용
	GetWorldTimerManager().SetTimer(
		FireDelayHandle,
		Del,
		RpmToDelayTime(),
		false
	);
}

void AFirearm::SetReloadDelay()
{
	if (bIsReloading) 
	{
		// 이미 장전 중
		return;
	}
	
	const FTimerDelegate ReloadDel = FTimerDelegate::CreateLambda([this]()->void
	{
		// Reload 메서드로 변경 가능
		// 총알 채울 양을 구한다.
		// 총알이 부족하면 그만큼만 채워야 하기에 CurrExtraAmmo와 비교한다.
		// 총알이 충분하다면 탄창이 빈 만큼 넣는다.
		
		// 클로즈드 볼트이고 약실에 총알이 있다면 총알 한 개를 더 채워야 한다.
		int32 AmmoInChamber = CurrentFirearmData->bIsClosedBolt && CurrMagAmmo != 0;
		
		int32 BulletAmountToAdd = FMath::Min(
			CurrentFirearmData->MagSize - CurrMagAmmo + AmmoInChamber,
			CurrExtraAmmo);
		
		// 여분 총알 BulletAmountToAdd 개를 장전된 총알 개수에 더한다
		CurrMagAmmo += BulletAmountToAdd;
		CurrExtraAmmo -= BulletAmountToAdd;
		
		bIsReloading = false;
	});
	
	bIsReloading = true;
	
	// 재장전 델리게이트를 타이머에 설정
	GetWorldTimerManager().SetTimer(
		ReloadDelayHandle,
		ReloadDel,
		CurrentFirearmData->ReloadTime,
		false
	);
}

void AFirearm::CancelReload()
{
	bIsReloading = false;
	
	// 장전 소리 멈춤
	if (ReloadSoundComp != nullptr)
		ReloadSoundComp->Stop();

	// 장전 애니메이션 멈춤
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->StopAnimMontage();

	// 재장전 딜레이 타이머 취소
	GetWorldTimerManager().ClearTimer(ReloadDelayHandle);
}


void AFirearm::OnUnequip_Implementation()
{
	Super::OnUnequip_Implementation();
	
	// cancel everything
	// 재장전 소리 비활성화
	CancelReload();
}
