// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on TankMovementComponent, MoveToActor->pathfinding->TankMovementComponent->RequestDirectMove.

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerTank = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		if (ensure(TankAimingComponent))
		{
			TankAimingComponent->AimAt(PlayerTank->GetTargetLocation(GetPawn()));
		}
	}

	// FIXME Temporarilly disable as it is a pain when you are trying to debug movement.
	//ControlledTank->Fire();
}

