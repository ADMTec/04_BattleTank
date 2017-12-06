// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Makes sure that parent implementation is being calling.
	UE_LOG(LogTemp, Warning, TEXT("Player Controler BeginPlay"))

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::BeginPlay() - PlayerController possesing: %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ATankPlayerController::BeginPlay() - PlayerController not possesing a tank."))
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


