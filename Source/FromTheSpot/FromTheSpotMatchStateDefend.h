// Written by Lewis Heath.

#pragma once

#include "CoreMinimal.h"
#include "FromTheSpotMatchStateBase.h"
#include "FromTheSpotMatchStateDefend.generated.h"

UCLASS()
class FROMTHESPOT_API UFromTheSpotMatchStateDefend : public UFromTheSpotMatchStateBase
{
	GENERATED_BODY()

public:
	UFromTheSpotMatchStateDefend();

	virtual void StartMatchState() override;

	virtual void TickMatchState(const float DeltaTime) override;

	virtual void EndMatchState() override;
};
