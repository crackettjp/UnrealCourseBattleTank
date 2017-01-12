// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ensure(ControlledTank || !ensure(PlayerTank))) return;

	MoveToActor(PlayerTank, AcceptanceRadius);
	ControlledTank->AimAt(PlayerTank->GetTargetLocation(ControlledTank));

	// FIXME Temporarilly disable as it is a pain when you are trying to debug movement.
	//ControlledTank->Fire();
}

