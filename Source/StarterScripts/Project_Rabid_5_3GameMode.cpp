// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_Rabid_5_3GameMode.h"
#include "Project_Rabid_5_3Character.h"
#include "UObject/ConstructorHelpers.h"

AProject_Rabid_5_3GameMode::AProject_Rabid_5_3GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
