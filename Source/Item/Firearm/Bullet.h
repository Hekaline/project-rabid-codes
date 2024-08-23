// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;

UCLASS()
class PROJECT_RABID_5_3_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitBullet(const int32 _PenetrateCnt, const float _Damage);

protected:
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	
protected:
	UPROPERTY()
	int32 PenetrateCnt = 1;

	UPROPERTY();
	float Damage = 25.f;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* BulletEffect;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;
};
