// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThunderstrikeGameMode.h"
#include "ThunderstrikeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThunderstrikeGameMode::AThunderstrikeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
