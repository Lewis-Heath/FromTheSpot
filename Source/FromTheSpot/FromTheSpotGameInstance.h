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

protected:
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FMatchData MatchData = FMatchData();
};
