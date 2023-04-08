// Written by Lewis Heath.

#include "Football.h"

#include "Kismet/KismetMathLibrary.h"

AFootball::AFootball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFootball::ResetToStart()
{
	// Check the football mesh is valid
	if (!IsValid(FootballMesh))
	{
		return;
	}

	// Reset the sound bools
	bNetSoundPlayed = false;
	bHittingGoalkeeperSoundPlayed = false;
	
	// Flip physics on and off for the ball and reset the actors position
	FootballMesh->SetSimulatePhysics(false);
	FootballMesh->SetWorldLocation(StartingLocation);
	FootballMesh->SetSimulatePhysics(true);
	FootballMesh->SetVisibility(true);
	FootballMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AFootball::Shoot(const FVector& TargetLocation, const float TimingMultiplier)
{
	// Check the football mesh is valid
	if (!IsValid(FootballMesh))
	{
		return;
	}
	
	// Calculate the final power multiplier
	float FinalPowerMultiplier = TimingMultiplier * PowerMultiplier;

	if (TimingMultiplier < 0.25f)
	{
		FinalPowerMultiplier = PowerMultiplier * 2.0f;
	}

	// Calculate the impulse force to be applied
	const FVector ImpulseForce = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), TargetLocation) * FinalPowerMultiplier;

	// Add the impulse force to the football
	FootballMesh->AddImpulse(ImpulseForce);
}

void AFootball::DampenVelocity(const float DampenMultiplier)
{
	// Check the football mesh is valid
	if (!IsValid(FootballMesh))
	{
		return;
	}

	// Get the dampen multiplier value
	const float FinalDampenMultiplier = 1 - DampenMultiplier;

	// Grab the current linear velocity
	const FVector CurrentLinearVelocity = FootballMesh->GetPhysicsLinearVelocity();

	// Update the velocity 
	FootballMesh->SetAllPhysicsLinearVelocity(CurrentLinearVelocity * FinalDampenMultiplier);
}

void AFootball::BeginPlay()
{
	Super::BeginPlay();

	// Set the starting location
	StartingLocation = GetActorLocation();
}
