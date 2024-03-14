// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APlatformPawn::APlatformPawn()
{
	SetReplicates(true);
	SetReplicateMovement(true);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCollideWhenPlacing = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent0"));
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CollisionComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent0"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, FName());

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	MovementComponent->UpdatedComponent = CollisionComponent;
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

// Called to bind functionality to input
void APlatformPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlatformPawn::RightMovementAction(float Value)
{
	if (Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
		ServerSetNewLocation(GetActorLocation());
	}
}

void APlatformPawn::ServerSetNewLocation_Implementation(const FVector& Location)
{
	SetActorLocation(Location);
}