// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController %s beginning play"), *GetName());

	ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController %s controlling tank %s"), *GetName(), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController %s has no controlled tank"), *GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ControlledTank) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (!ControlledTank) return false;

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
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s unable to deproject crosshair"), *GetName());
	}

	return false;
}
