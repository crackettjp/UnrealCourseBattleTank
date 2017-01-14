// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(TankAimingComponent))
	{
		FoundAimingComponent(TankAimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) return; // If not possessing.
	if (!ensure(TankAimingComponent)) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("aim solution"));
		TankAimingComponent->AimAt(HitLocation);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("NO aim solution"));
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the cross hair location on the screen in pixels.
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// SEE GetHitResultAtScreenPosition()!

	// Find the unit vector direction of the cross hair
	FVector CameraWorldLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, CameraWorldLocation, WorldDirection))
	{
		// Ray-trace out to see if / what we hit something
		FHitResult HitResult;
		FVector TraceEnd = CameraWorldLocation + WorldDirection * LineTraceRange;
		// FIXME hits the SkySphere
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetPawn());
		if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraWorldLocation, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams))
		{
			HitLocation = HitResult.ImpactPoint;
			return true;
		}
	}

	return false;
}
