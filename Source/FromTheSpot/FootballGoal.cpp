// Written by Lewis Heath.

#include "FootballGoal.h"
#include "Kismet/KismetMathLibrary.h"

FDivePointInfo AFootballGoal::GetDiveInfo(const FVector& TargetLocation) const
{
	// Set the default variables
	float ClosestDistance = 1000000.0f;
	FDivePointInfo ClosestDiveInfo = FDivePointInfo();

	// Loop through each dive point
	for (const FDivePointInfo& DivePointInfo : DivePoints)
	{
		// Calculate the distance between the location passed in and the dive point location
		const float CurrentDistance = UKismetMathLibrary::Vector_Distance(TargetLocation, DivePointInfo.TargetPoint->GetComponentLocation());

		// Is the current smaller than the closest 
		if (CurrentDistance < ClosestDistance)
		{
			// Set the new closest
			ClosestDistance = CurrentDistance;
			ClosestDiveInfo = DivePointInfo;
		}
	}

	// Return the closest dive info
	return ClosestDiveInfo;
}

FVector AFootballGoal::GetRandomBadShotLocation() const
{
	// Set the default variable 
	FVector RandomLocation = FVector::ZeroVector;

	// Grab a random index within the arrays range
	const int RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, BadShotPoints.Num()-1);

	// Check the index is valid
	if (!BadShotPoints.IsValidIndex(RandomIndex))
	{
		return RandomLocation;
	}

	// Get the random point scene component
	const USceneComponent* RandomPoint = BadShotPoints[RandomIndex];

	// Check its valid
	if (!IsValid(RandomPoint))
	{
		return RandomLocation;
	}

	// Set the random location and return it
	RandomLocation = RandomPoint->GetComponentLocation();
	return RandomLocation;
}



