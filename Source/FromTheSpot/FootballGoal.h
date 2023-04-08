// Written by Lewis Heath.

#pragma once

#include "CoreMinimal.h"
#include "FromTheSpotDataTypes.h"
#include "GameFramework/Actor.h"
#include "FootballGoal.generated.h"

UCLASS()
class FROMTHESPOT_API AFootballGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Returns the dive info based on the target location passed in 
	UFUNCTION(BlueprintCallable)
	FDivePointInfo GetDiveInfo(const FVector& TargetLocation) const;

	// Returns a random bad shot location from the bad shot points array
	UFUNCTION(BlueprintCallable)
	FVector GetRandomBadShotLocation() const;

protected:
	// Array holding the info for the different dive points 
	UPROPERTY(BlueprintReadWrite)
	TArray<FDivePointInfo> DivePoints;

	// Array holding the different bad shot points
	UPROPERTY(BlueprintReadWrite)
	TArray<USceneComponent*> BadShotPoints;
};
