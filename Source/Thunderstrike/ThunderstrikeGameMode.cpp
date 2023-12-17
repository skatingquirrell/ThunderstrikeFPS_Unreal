// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThunderstrikeGameMode.h"
#include "ThunderstrikeCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AThunderstrikeGameMode::AThunderstrikeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AThunderstrikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &AThunderstrikeGameMode::CountDownTimer, 1.0f, true, 1.0f);
}

void AThunderstrikeGameMode::RestartGameplay(bool Won)
{
	if (Won)
	{
		HasWon = true;
		ResetLevel();
	}
	else
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AThunderstrikeGameMode::ResetLevel, 3.0f);
		UE_LOG(LogTemp, Warning, TEXT("restart game play after 3 seconds"));
	}
}

void AThunderstrikeGameMode::ResetLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ThunderstrikeMap");
	UE_LOG(LogTemp, Warning, TEXT("restart map"));
}

void AThunderstrikeGameMode::CountDownTimer()
{
	TimerCount--;
	if (TimerCount < 0)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		ResetLevel();
	}
}