// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track that may apply a force to its owning body through a throttle.  Applies force in the forward direction of the owning tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// Track max driving force in Newtons.
	UPROPERTY(EditDefaultsOnly, Category="Input")
	float TrackDrivingForce = 400000; // 40 tonne tank, 1G.

private:
	UTankTrack();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
