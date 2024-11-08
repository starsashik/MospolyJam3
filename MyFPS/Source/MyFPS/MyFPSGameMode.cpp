// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFPSGameMode.h"
#include "MyFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyFPSGameMode::AMyFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
