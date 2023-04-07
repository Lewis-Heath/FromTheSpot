// Written by Lewis Heath.

#include "FootballGoal.h"
#include "Kismet/KismetMathLibrary.h"

AFootballGoal::AFootballGoal()
{
	
}

FDivePointInfo AFootballGoal::GetDiveInfo(const FVector& TargetLocation) const
{
	float ClosestDistance = 1000000.0f;
	FDivePointInfo ClosestDiveInfo = FDivePointInfo();

	for (const FDivePointInfo& DivePointInfo : DivePoints)
	{
		const float CurrentDistance = UKismetMathLibrary::Vector_Distance(TargetLocation, DivePointInfo.TargetPoint->GetComponentLocation());

		if (CurrentDistance < ClosestDistance)
		{
			ClosestDistance = CurrentDistance;
			ClosestDiveInfo = DivePointInfo;
		}
	}

	return ClosestDiveInfo;
}

FVector AFootballGoal::GetRandomBadShotLocation() const
{
	FVector RandomLocation = FVector::ZeroVector;
	
	const int RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, BadShotPoints.Num()-1);

	if (!BadShotPoints.IsValidIndex(RandomIndex))
	{
		return RandomLocation;
	}

	const USceneComponent* RandomPoint = BadShotPoints[RandomIndex];

	if (!IsValid(RandomPoint))
	{
		return RandomLocation;
	}

	RandomLocation = RandomPoint->GetComponentLocation();
	return RandomLocation;
}



