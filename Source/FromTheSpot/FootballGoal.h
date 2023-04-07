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
	// Sets default values for this actor's properties
	AFootballGoal();

	//
	UFUNCTION(BlueprintCallable)
	FDivePointInfo GetDiveInfo(const FVector& TargetLocation) const;

	//
	UFUNCTION(BlueprintCallable)
	FVector GetRandomBadShotLocation() const;

protected:
	//
	UPROPERTY(BlueprintReadWrite)
	TArray<FDivePointInfo> DivePoints;

	//
	UPROPERTY(BlueprintReadWrite)
	TArray<USceneComponent*> BadShotPoints;
};
