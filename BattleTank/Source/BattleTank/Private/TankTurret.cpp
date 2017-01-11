
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto NewYaw = this->RelativeRotation.Yaw + RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	this->SetRelativeRotation(FRotator(0.0f, NewYaw, 0.0f));
}


