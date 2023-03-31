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
	UFromTheSpotMatchStateCoinFlip();

	virtual void StartMatchState() override;

	virtual void TickMatchState(const float DeltaTime) override;

	virtual void EndMatchState() override;

protected:
	ECoinFlipResult CoinFlipResult = ECoinFlipResult::NONE;

	float CoinFlipDecisionTime = 1.0f;
};
