// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController %s has no controlled tank"), *GetName());
	}

	PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController %s unable to find player tank"), *GetName());
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick();
	if (!ControlledTank || !PlayerTank) return;
	ControlledTank->AimAt(PlayerTank->GetTargetLocation(ControlledTank));
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}
