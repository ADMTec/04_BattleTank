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
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - AITank %s - AIController found player %s"), *this->GetControlledTank()->GetName(), *PlayerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - AIController not found player."))
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds); // I call base clase implementation just fot extend functionality

	ATank * PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		// TODO: move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
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
		//UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - PlayerController name %s"), *PC->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay() - AIController not found PlayerController"))
		return nullptr;
	}

	return Cast<ATank>(PC->GetPawn());
}
