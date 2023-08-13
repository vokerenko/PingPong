// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"

// Sets default values
APlatformPawn::APlatformPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(StaticMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlatformPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformPawn::ServerMoveVertical_Implementation(float AxisValue)
{
	MulticastMoveVertical(AxisValue);
}
void APlatformPawn::MulticastMoveVertical_Implementation(float AxisValue)
{
	FVector Right = GetActorRightVector();
	FVector Delta = Right * Speed * AxisValue;
	AddActorWorldOffset(Delta, true);
}
