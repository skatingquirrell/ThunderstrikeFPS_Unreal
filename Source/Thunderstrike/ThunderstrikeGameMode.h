// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThunderstrikeGameMode.generated.h"

UCLASS(minimalapi)
class AThunderstrikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThunderstrikeGameMode();

	void RestartGameplay(bool Won);

private:
	void ResetLevel();

public:
	UPROPERTY(BlueprintReadOnly)
	int TimerCount = 300;

	UPROPERTY(BlueprintReadOnly)
	bool HasWon = false;

private:
	FTimerHandle CountDownTimerHandle = FTimerHandle();
	void CountDownTimer();

public:
	void BeginPlay() override;
};
