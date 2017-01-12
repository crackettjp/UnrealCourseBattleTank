// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();  // FIXME check if saving this is really worth it

	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(ControlledTank)) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (!ensure(ControlledTank)) return false;

	// Find the crosshair location on the screen in pixels.
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrosshairScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// SEE GetHitResultAtScreenPosition()!

	// Find the unit vector direction of the crosshair
	FVector CameraWorldLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, CameraWorldLocation, WorldDirection))
	{
		// Ray-trace out to see if / what we hit something
		FHitResult HitResult;
		FVector TraceEnd = CameraWorldLocation + WorldDirection * LineTraceRange;
		// FIXME hits the SkySphere
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, ControlledTank);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraWorldLocation, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams))
		{
			HitLocation = HitResult.ImpactPoint;
			return true;
		}
	}

	return false;
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
