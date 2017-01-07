// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController %s beginning play"), *GetName());

	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController %s controlling tank %s"), *GetName(), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController %s has no controlled tank"), *GetName());
	}
}

ATank * ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}
