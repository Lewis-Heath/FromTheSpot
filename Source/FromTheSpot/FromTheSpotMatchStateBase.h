// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotDataTypes.h"
#include "FromTheSpotMatchStateBase.generated.h"

class AFromTheSpotGameModeBase;

UCLASS()
class FROMTHESPOT_API UFromTheSpotMatchStateBase : public UObject
{
	GENERATED_BODY()

public:
	UFromTheSpotMatchStateBase();

	virtual void StartMatchState();

	virtual void TickMatchState(const float DeltaTime);

	virtual void EndMatchState();

	virtual void SetGameModeReference(AFromTheSpotGameModeBase* NewGameModeReference);

	virtual void SetMaxTimeInProgress(const float NewMaxTime);
	virtual float GetMaxTimeInProgress() const;

	virtual float GetCurrentTimeInProgress() const;

protected:
	UPROPERTY()
	AFromTheSpotGameModeBase* GameModeReference = nullptr;
	
	EMatchState MatchStateType = EMatchState::NONE;
	float MaxTimeInProgress = -1.0f;
	float CurrentTimeInProgress = 0.0f;
};
