// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
// Depends on TankMovementComponent, MoveToActor->pathfinding->TankMovementComponent->RequestDirectMove.

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	if (ensure(ControlledTank))
	{
		TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	}

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ensure(ControlledTank) || !ensure(TankAimingComponent) || !ensure(PlayerTank)) return;

	MoveToActor(PlayerTank, AcceptanceRadius);
	TankAimingComponent->AimAt(PlayerTank->GetTargetLocation(ControlledTank));

	// FIXME Temporarilly disable as it is a pain when you are trying to debug movement.
	//ControlledTank->Fire();
}

