// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// He did this every time in Tick().

	ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController %s has no controlled tank"), *GetName());
	}

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController %s unable to find player tank"), *GetName());
	}

	if (ControlledTank && PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController %s controlling %s attacking %s"), *GetName(), *ControlledTank->GetName(), *PlayerTank->GetName())
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ControlledTank || !PlayerTank) return;

	MoveToActor(PlayerTank, AcceptanceRadius);
	ControlledTank->AimAt(PlayerTank->GetTargetLocation(ControlledTank));
	//ControlledTank->Fire();
}

