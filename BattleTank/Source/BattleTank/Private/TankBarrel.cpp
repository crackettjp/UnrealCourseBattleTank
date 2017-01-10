// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	auto NewPitch = FMath::Clamp<float>(this->RelativeRotation.Pitch + RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds, MinElevationDegrees, MaxElevationDegrees);
	this->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));
}


