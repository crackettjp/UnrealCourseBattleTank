// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void LaunchProjectile(float Speed);

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* LaunchBlast = nullptr;

	UProjectileMovementComponent* ProjectileMovement = nullptr;
};
