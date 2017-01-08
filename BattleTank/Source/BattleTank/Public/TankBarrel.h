// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Elevatable tank barrel component.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditAnywhere)
	float MinElevationDegrees = -2.0f;

	UPROPERTY(EditAnywhere)
	float MaxElevationDegrees = 40.0f;
};
