// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotMatchStateBase.h"
#include "FromTheSpotMatchStateInteraction.generated.h"

UCLASS()
class FROMTHESPOT_API UFromTheSpotMatchStateInteraction : public UFromTheSpotMatchStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this objects properties
	UFromTheSpotMatchStateInteraction();

	// Called when the match state is started
	virtual void StartMatchState() override;

	// Called when the match state is ended
	virtual void EndMatchState() override;
	
protected:
	// Tells the game mode to start the penalty
	virtual void BlowWhistle();

	// Timer for the penalty start
	FTimerHandle WhistleTimerHandle;

	// Timer amount
	float WhistleTime = 1.0f;
};
