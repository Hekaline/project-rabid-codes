// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "ItemDataAsset.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AppearanceMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Appearance Mesh");
	AppearanceMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	if (Data == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Data is not found!"));
		return;
	}

	Name = Data->Name;
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

