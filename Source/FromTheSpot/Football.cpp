// Written by Lewis Heath.

#include "Football.h"

#include "Kismet/KismetMathLibrary.h"

AFootball::AFootball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	if (!IsValid(Root))
	{
		return;
	}

	// Create the mesh
	FootballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FootballMesh"));
	FootballMesh->SetupAttachment(Root);
}

void AFootball::ResetToSpot()
{
	// Check the football mesh is valid
	if (!IsValid(FootballMesh))
	{
		return;
	}

	// Flip physics on and off for the ball and reset the actors position
	FootballMesh->SetSimulatePhysics(false);
	FootballMesh->SetWorldLocation(StartingLocation);
	FootballMesh->SetSimulatePhysics(true);
}

void AFootball::Shoot(const FVector& TargetLocation, const float TimingMultiplier)
{
	// Check the football mesh is valid
	if (!IsValid(FootballMesh))
	{
		return;
	}

	// Calculate the final power multiplier
	const float FinalPowerMultiplier = TimingMultiplier * PowerMultiplier;

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
