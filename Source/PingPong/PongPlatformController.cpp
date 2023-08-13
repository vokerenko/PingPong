// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformPawn.h"
#include "PongPlatformController.h"


void APongPlatformController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveVertical", this, &APongPlatformController::MoveVertical);
}

void APongPlatformController::MoveVertical(float AxisValue)
{
	APawn* ControlledPawn = GetPawn();
	if (APlatformPawn* Platform = Cast<APlatformPawn>(ControlledPawn))
	{
		Platform->ServerMoveVertical(AxisValue);
	}

}