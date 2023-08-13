// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlatformController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APongPlatformController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	void MoveVertical(float AxisValue);
};
