// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); // Makes sure that parent implementation is being calling.
	
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - AIController found player %s"), *PlayerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - AIController not found player."))
	}

}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController * PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - PlayerController name %s"), *PC->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - AIController not found PlayerController"))
		return nullptr;
	}

	return Cast<ATank>(PC->GetPawn());
}
