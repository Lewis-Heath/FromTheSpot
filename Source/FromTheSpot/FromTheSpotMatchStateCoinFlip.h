// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotMatchStateBase.h"
#include "FromTheSpotMatchStateCoinFlip.generated.h"

UCLASS()
class FROMTHESPOT_API UFromTheSpotMatchStateCoinFlip : public UFromTheSpotMatchStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this objects properties
	UFromTheSpotMatchStateCoinFlip();

	// Called every frame while the match state is active
	virtual void TickMatchState(const float DeltaTime) override;

protected:
	// The result of the coin flip
	ECoinFlipResult CoinFlipResult = ECoinFlipResult::NONE;

	// The amount of time before the coin flip logic is played
	float CoinFlipDecisionTime = 1.0f;
};
