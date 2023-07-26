// Copyright Epic Games, Inc. All Rights Reserved.

#include "InfluenceMapGameMode.h"
#include "InfluenceMapCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInfluenceMapGameMode::AInfluenceMapGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
