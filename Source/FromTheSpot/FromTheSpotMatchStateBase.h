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
	// Sets default values for this objects properties
	UFromTheSpotMatchStateBase();

	// Called when the match state is started
	virtual void StartMatchState();

	// Called every frame while the match state is active
	virtual void TickMatchState(const float DeltaTime);

	// Called when the match state is ended
	virtual void EndMatchState();

	// Sets the game mode reference 
	virtual void SetGameModeReference(AFromTheSpotGameModeBase* NewGameModeReference);

	// Sets the max time in progress variable
	virtual void SetMaxTimeInProgress(const float NewMaxTime);

	// Returns the max time in progress variable
	virtual float GetMaxTimeInProgress() const;

	// Returns the current elapsed time the state has been active
	virtual float GetCurrentTimeInProgress() const;

	// Sets the round timer to true
	virtual void ActivateRoundTimer(const bool bActive);

protected:
	// Reference to the game mode
	UPROPERTY(BlueprintReadOnly)
	AFromTheSpotGameModeBase* GameModeReference = nullptr;

	// The match state type 
	EMatchState MatchStateType = EMatchState::NONE;

	// The max time the state can be in progress, -1.0f = no limit
	float MaxTimeInProgress = -1.0f;

	// The current time the state has been active
	float CurrentTimeInProgress = 0.0f;

	// Is the match state timer active
	bool bTimerActive = false;
};
