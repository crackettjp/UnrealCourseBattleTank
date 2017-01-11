// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();
	void SetBarrel(UTankBarrel *BarrelToSet);
	void SetTurret(UTankTurret *TurretToSet);
	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
};
