// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;

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

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) return;

	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) return;

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;
	Barrel->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Turret)) return;

	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - TurretRotation;
	Turret->Rotate(DeltaRotation.GetNormalized().Yaw);
}
