// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
//#include "GameFramework/FloatingPawnMovement.h"
#include "PlatformPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCollideWhenPlacing = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent0"));
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CollisionComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent0"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	//MovementComponent->UpdatedComponent = CollisionComponent;

	
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABall::OnCollision);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(Velocity * Speed, true);
}

void ABall::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (APlatformPawn* Pawn = Cast<APlatformPawn>(OtherActor))
	{
		FVector Origin;
		FVector PlatformHalfSize;
		Pawn->GetActorBounds(true, Origin, PlatformHalfSize, true);
		Velocity = FVector(-Velocity.X, (GetActorLocation().Y - Pawn->GetActorLocation().Y ) / (PlatformHalfSize.Y), 0.0f);
	}
	else
	{
		Velocity = FVector(-Velocity.Y, Velocity.X, 0.0f);
		Velocity *= FMath::Sign(Velocity.Dot(Hit.Normal));
	}
}

