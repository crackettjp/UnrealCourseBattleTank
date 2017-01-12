// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;
	if (!Turret) return;

	FVector LaunchVelocity;
	FCollisionResponseParams ResponseParams;
	TArray<AActor*> ActorsToIgnore;
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, Barrel->GetSocketLocation(FName("Projectile")), HitLocation, LaunchSpeed, false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace, ResponseParams, ActorsToIgnore, false)) // Must supply DoNotTrace or will bug out.
	{
		MoveBarrelTowards(LaunchVelocity.GetSafeNormal());
		MoveTurretTowards(LaunchVelocity.GetSafeNormal());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) return;

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	Barrel->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!Turret) return;

	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - TurretRotation;
	Turret->Rotate(DeltaRotation.GetNormalized().Yaw);
}

