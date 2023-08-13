// Copyright Epic Games, Inc. All Rights Reserved.

#include "PongPlatformController.h"
#include "GameFramework/PlayerController.h"
#include "PingPongGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Logging/LogMacros.h"

void APingPongGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NumberOfPlayers == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue,  "Waiting for a second player to start the game");
	}
}
APingPongGameModeBase::APingPongGameModeBase()
{
	BallDestroyedDelegate.BindUFunction(this, "StartSpawnBallTimer");
}

AActor* APingPongGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> FoundStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundStarts);
	for (AActor*& Actor : FoundStarts)
	{
		if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
		{
			if (PlayerStart->PlayerStartTag != "Taken")
			{
				PlayerStart->PlayerStartTag = "Taken";
				return PlayerStart;
			}
		}
	}

	return AGameModeBase::ChoosePlayerStart(Player);
}

UFUNCTION()
void APingPongGameModeBase::StartSpawnBallTimer()
{
	float Duration = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APingPongGameModeBase::SpawnBallCallback, Duration);
}

void APingPongGameModeBase::SpawnBallCallback()
{
	FTransform BallInitialTransform = FTransform(FVector(30.0f, -170.0f, -30.0f));
	if (AActor* SpawnedBall = GetWorld()->SpawnActor(BallClass, &BallInitialTransform))
	{
		Ball = Cast<ABall>(SpawnedBall);
		Ball->OnDestroyed.Add(BallDestroyedDelegate);
	}
	if (!bHasSpawnedHUD)
	{
		for (APongPlatformController*& PC : Players)
		{
			PC->ClientSetHUD(PongHUDClass);
		}
		bHasSpawnedHUD = true;
	}
}


void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (APongPlatformController* PC = Cast<APongPlatformController>(NewPlayer))
	{
		Players.Add(PC);
	}
	NumberOfPlayers++;

	GEngine->AddOnScreenDebugMessage(-1, 5.0F, FColor::Blue, 
		"The player " + FString::FromInt(NumberOfPlayers) + 
		" has joined a game");
	if (NumberOfPlayers == 2)
	{
		StartSpawnBallTimer();
	}
}
