// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankBarrel.h"
#include "Runtime/engine/Classes/Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation, and AimDirection
	FRotator BarrelRotator = this->Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(5.f); // TODO: remove magic number
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!this->Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = this->Barrel->GetSocketLocation(FName("Projectile"));
	FVector EndLocation = HitLocation;
	float TossSpeed = LaunchSpeed;
	
	// Be careful with the parameters! other way don't works for me.
	/* TraceFullPath means when it hit the ground or tank then it would 
	   fail as something is blocking it meaning the result returned 
	   would be false.
	 */
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		EndLocation,
		TossSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::AimAt() - bHaveAimSolution %s"), bHaveAimSolution ? TEXT("true") : TEXT("false"))

	if (bHaveAimSolution)
	{
		// Calculate the OutLaunchVelocity 
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		FString TankName = this->GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::AimAt() - %s Aiming at %s"), *TankName, *AimDirection.ToString())

		MoveBarrelTowards(HitLocation);
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: UTankAimingComponent::AimAt() - Aim solution found"), Time)
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: UTankAimingComponent::AimAt() - No aim solve found"), Time)
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

