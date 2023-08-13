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

	/*
	* Choose not taken player start
	* @return Free player start
	*/
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void Tick(float DeltaTime) override;

	/*
	* After all players are connected spawns the ball
	*/
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	/*
	* 1 second timer for SpawnBallCallback()
	*/
	UFUNCTION(BlueprintCallable)
	void StartSpawnBallTimer();

	/*
	* Spawns a ball into the world, binds OnDestroyed event to StartSpawnBallTimer(),
	* if HUD is not set it will set the HUD for players
	*/
	void SpawnBallCallback();

private:
	/*
	* Range from 0 to 2
	*/
	UPROPERTY()
	int NumberOfPlayers = 0;

	/*
	* Used for creating widgets
	*/
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
