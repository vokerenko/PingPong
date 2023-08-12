// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PongPlatformController.h"
#include "Ball.h"
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
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	UPROPERTY()
	int NumberOfPlayers = 0;

	UPROPERTY()
	TArray<APongPlatformController*> Players;

	UPROPERTY()
	ABall* Ball;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABall> BallClass;
	
};
