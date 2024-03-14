// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APlatformPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void SetupInputComponent() override;

	virtual void BindActions(class UInputMappingContext* Context);
protected:
	UFUNCTION()
	void RightMovementAction(const FInputActionValue& Value);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> DefaultInputMappingContext = nullptr;
};
