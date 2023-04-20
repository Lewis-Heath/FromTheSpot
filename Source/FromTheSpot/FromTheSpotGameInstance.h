// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FromTheSpotDataTypes.h"
#include "FromTheSpotGameInstance.generated.h"

UCLASS()
class FROMTHESPOT_API UFromTheSpotGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this game instance properties
	UFromTheSpotGameInstance();

	// Sets the data for this match
	UFUNCTION(BlueprintCallable)
	void SetMatchData(const FMatchData& NewMatchData);

	// Returns the match data
	UFUNCTION(BlueprintCallable)
	FMatchData GetMatchData() const;

	// Sets the volume array
	UFUNCTION(BlueprintCallable)
	void SetMatchVolumes(const TArray<float>& NewMatchVolumes);

	// Returns the volume array
	UFUNCTION(BlueprintCallable)
	TArray<float> GetMatchVolumes() const;

	// Returns the volume multiplier depending on index
	UFUNCTION(BlueprintCallable)
	float GetVolumeMultiplier(const int TypeIndex) const;

protected:
	// The data for this match
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FMatchData MatchData = FMatchData();

	// The volumes for the game 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<float> MatchVolumes;
};
