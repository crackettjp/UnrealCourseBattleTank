// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto DeltaPitch = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRelativeRotation = this->RelativeRotation;
	NewRelativeRotation.Pitch = FMath::Clamp<float>(NewRelativeRotation.Pitch + DeltaPitch, MinElevationDegrees, MaxElevationDegrees);
	this->SetRelativeRotation(NewRelativeRotation);
}


