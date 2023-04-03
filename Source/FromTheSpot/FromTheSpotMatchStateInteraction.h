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
	UFromTheSpotMatchStateInteraction();

	virtual void StartMatchState() override;

	virtual void TickMatchState(const float DeltaTime) override;

	virtual void EndMatchState() override;
	
protected:
	virtual void BlowWhistle();

	virtual void TakePenalty();
	
	FTimerHandle WhistleTimerHandle;
	float WhistleTime = 1.0f;

	FTimerHandle KickBallTimerHandle;
	float KickBallTime = 2.5f;
};
