// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

private:
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
};
