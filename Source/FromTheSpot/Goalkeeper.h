// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotDataTypes.h"
#include "GameFramework/Actor.h"
#include "Goalkeeper.generated.h"

UCLASS()
class FROMTHESPOT_API AGoalkeeper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalkeeper();

	UFUNCTION(BlueprintCallable)
	void ResetToStart();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Dive(const FDivePointInfo& DiveInfo);
};
