// Copyright Epic Games, Inc. All Rights Reserved.

#include "IMGameMode.h"
#include "IMCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIMGameMode::AIMGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
