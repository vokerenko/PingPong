// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	BeginOverlapDelegate.BindUFunction(this, "BeginOverlap");
}

void ABall::OnConstruction(const FTransform& Transform)
{
	float x = 1.0f;
	float y = 1.0f;
	if (FMath::RandBool())
	{
		x = -1.0f;
	}
	if (FMath::RandBool())
	{
		y = -1.0f;
	}
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bBounceAngleAffectsFriction = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1200.0f;
	ProjectileMovement->Velocity = FVector(x, y, 0.0f);

	OnActorBeginOverlap.Add(BeginOverlapDelegate);
}

void ABall::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PawnClass, FoundActors);
	if (FoundActors.Num() == 2)
	{
		if (OtherActor->ActorHasTag("Player"))
		{
			if (APlatformPawn* Pawn = Cast<APlatformPawn>(FoundActors[0]))
			{
				Pawn->IncrementScore();
			}
		}
		if (OtherActor->ActorHasTag("Enemy"))
		{
			if (APlatformPawn* Pawn = Cast<APlatformPawn>(FoundActors[1]))
			{
				Pawn->IncrementScore();
			}
		}
	}
	Destroy();
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



