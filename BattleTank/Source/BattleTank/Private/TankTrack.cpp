// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	bWantsBeginPlay = true;
}

void UTankTrack::BeginPlay()
{
	PrimaryComponentTick.bCanEverTick = true;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector CorrectAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit: %s %s %s %s"), *HitComponent->GetName(), *OtherActor->GetName(), *OtherComp->GetName(), *NormalImpulse.ToString());
}

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * Throttle * TrackDrivingForce;
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // Cast gets the first component to which force may be applied (see class viewer).
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
