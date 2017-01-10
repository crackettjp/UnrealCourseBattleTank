// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// FIXME clamp throttle value so player cant overdrive.
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s force %f"), GetWorld()->GetTimeSeconds(), *GetName(), Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * TrackDrivingForce;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // Cast gets the first component to which force may be applied (see class viewer).
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s force %s"), GetWorld()->GetTimeSeconds(), *GetName(), *ForceApplied.ToString());
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
