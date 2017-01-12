// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	ATank();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr; // FIXME remove

	double LastFireTime = 0;
};
