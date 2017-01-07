// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	ATank *ControlledTank;
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	UPROPERTY(EditAnywhere, Category="UI Crosshair")
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere, Category = "UI Crosshair")
	float CrossHairYLocation = 1.0f/3.0f;

	void ATankPlayerController::AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
