// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PINGPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//TObjectPtr<class UPawnMovementComponent> MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Speed = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity = FVector(1.0f, 1.0f, 0.0f);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit);
};
