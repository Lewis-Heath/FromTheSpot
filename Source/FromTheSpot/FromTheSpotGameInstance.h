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

	//
	UFUNCTION(BlueprintCallable)
	void SetMatchData(const FMatchData& NewMatchData);

	//
	UFUNCTION(BlueprintCallable)
	FMatchData GetMatchData() const;

	//
	UFUNCTION(BlueprintCallable)
	void SetMatchVolumes(const TArray<float>& NewMatchVolumes);

	//
	UFUNCTION(BlueprintCallable)
	TArray<float> GetMatchVolumes() const;

	UFUNCTION(BlueprintCallable)
	float GetVolumeMultiplier(const int TypeIndex) const;

protected:
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FMatchData MatchData = FMatchData();

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<float> MatchVolumes;
};
