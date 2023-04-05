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


