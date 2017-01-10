// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackDrivingForce;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // Cast gets the first component to which force may be applied (see class viewer).
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
