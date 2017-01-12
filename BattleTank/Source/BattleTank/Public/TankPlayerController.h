// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;


/**
 * Link the movement and firing of the player tank
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* TankAimingComponent);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void ATankPlayerController::AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	ATank *ControlledTank = nullptr;
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="UI Crosshair")
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "UI Crosshair")
	float CrossHairYLocation = 1.0f / 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "UI Crosshair")
	float LineTraceRange = 1000000;
};
