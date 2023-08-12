// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Logging/LogMacros.h"


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

void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (APongPlatformController* PC = Cast<APongPlatformController>(NewPlayer))
	{
		Players.Add(PC);
	}
	NumberOfPlayers++;
	if (NumberOfPlayers == 2)
	{
		FTransform BallInitialTransform = FTransform(FVector(30.0f, -170.0f, -30.0f));
		if (AActor* SpawnedBall = GetWorld()->SpawnActor(BallClass, &BallInitialTransform))
		{
			Ball = Cast<ABall>(SpawnedBall);
		}
		
	}
}
