// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// His way condensed.
	auto NewPitch = FMath::Clamp<float>(this->RelativeRotation.Pitch + RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds, MinElevationDegrees, MaxElevationDegrees);
	this->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));

	// I think something like this is more general purpose but may you always make the other relative rotations 0.0 in the BP?
	//auto DeltaPitch = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	//auto NewRelativeRotation = this->RelativeRotation;
	//UE_LOG(LogTemp, Warning, TEXT("barrel relative rotation %s"), *NewRelativeRotation.ToString());
	//NewRelativeRotation.Pitch = FMath::Clamp<float>(NewRelativeRotation.Pitch + DeltaPitch, MinElevationDegrees, MaxElevationDegrees);
	//this->SetRelativeRotation(NewRelativeRotation);
}


