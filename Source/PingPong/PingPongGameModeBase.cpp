// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

	AActor* APingPongGameModeBase::ChoosePlayerStart(AController* Player)
	{
		TArray<AActor*> FoundStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundStarts);
		for (AActor* Actor : FoundStarts)
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
		return Super::ChoosePlayerStart(Player);
	}