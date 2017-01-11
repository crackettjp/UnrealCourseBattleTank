// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * Link the movement and firing of the player tank to the 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void ATankPlayerController::AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	ATank *ControlledTank;

	UPROPERTY(EditDefaultsOnly, Category="UI Crosshair")
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "UI Crosshair")
	float CrossHairYLocation = 1.0f / 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "UI Crosshair")
	float LineTraceRange = 1000000;
};
