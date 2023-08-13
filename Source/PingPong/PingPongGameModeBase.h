// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PongPlatformController.h"
#include "Ball.h"
#include "PongHUD.h"
#include "TimerManager.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APingPongGameModeBase();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
private:
	UFUNCTION(BlueprintCallable)
	void StartSpawnBallTimer();

	void SpawnBallCallback();

private:
	UPROPERTY()
	int NumberOfPlayers = 0;

	UPROPERTY()
	TArray<APongPlatformController*> Players;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABall* Ball;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABall> BallClass;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APongHUD> PongHUDClass;

	FTimerHandle TimerHandle;

	bool bHasSpawnedHUD = false;

	FScriptDelegate BallDestroyedDelegate;
};
