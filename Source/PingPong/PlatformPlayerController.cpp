// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "PlatformPawn.h"

void APlatformPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionEventBindings();
		EnhancedInputComponent->ClearActionValueBindings();
		EnhancedInputComponent->ClearDebugKeyBindings();
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (!DefaultInputMappingContext.IsNull())
				{
					InputSystem->AddMappingContext(DefaultInputMappingContext.LoadSynchronous(), 0);
				}
			}
		}
		BindActions(DefaultInputMappingContext.LoadSynchronous());
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("PingPong requires Enhanced Input System to be activated in project settings to function properly"));
	}
}

void APlatformPlayerController::BindActions(UInputMappingContext* Context)
{
	if (Context)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("BindToContext"));
		const TArray<FEnhancedActionKeyMapping>& Mappings = Context->GetMappings();
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComponent)
		{
			TSet<const UInputAction*> UniqueActions;
			for (const FEnhancedActionKeyMapping& Keymapping : Mappings)
			{
				UniqueActions.Add(Keymapping.Action);
			}
			for (const UInputAction* UniqueAction : UniqueActions)
			{
				EnhancedInputComponent->BindAction(UniqueAction, ETriggerEvent::Triggered, Cast<UObject>(this), FName(UniqueAction->GetName()));
			}
		}
	}
}


void APlatformPlayerController::RightMovementAction(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("RightMovement"));
	if (APawn* MyPawn = GetPawn())
	{
		if (APlatformPawn* Platform = Cast<APlatformPawn>(MyPawn))
		{
			Platform->RightMovementAction(Value.GetMagnitude());
		}
	}

}