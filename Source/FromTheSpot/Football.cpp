// Written by Lewis Heath.

#include "Football.h"

AFootball::AFootball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a mesh
	FootballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FootballMesh"));
	FootballMesh->SetupAttachment(RootComponent);
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
	SetActorLocation(StartingLocation);
	FootballMesh->SetSimulatePhysics(true);
}

void AFootball::Shoot(const FVector& TargetLocation, const float TimingMultiplier)
{
	
}

void AFootball::DampenVelocity(const float DampenMultiplier)
{
	const float FinalDampenMultiplier = 1 - DampenMultiplier;
	
}

void AFootball::BeginPlay()
{
	Super::BeginPlay();

	// Set the starting location
	StartingLocation = GetActorLocation();
}
