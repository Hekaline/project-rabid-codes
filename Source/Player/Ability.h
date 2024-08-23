// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ability.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_RABID_5_3_API IAbility
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 함수에 = 0을 하면 가상 함수가 된다.
	// 추상 클래스(인터페이스) 구현에 사용됨
	virtual void UseAbility() = 0;
};
