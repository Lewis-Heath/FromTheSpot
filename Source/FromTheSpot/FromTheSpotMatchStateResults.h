// Written by Lewis Heath.

#pragma once

#include "CoreMinimal.h"
#include "FromTheSpotMatchStateBase.h"
#include "FromTheSpotMatchStateResults.generated.h"

UCLASS()
class FROMTHESPOT_API UFromTheSpotMatchStateResults : public UFromTheSpotMatchStateBase
{
	GENERATED_BODY()

public:
	UFromTheSpotMatchStateResults();

	virtual void StartMatchState() override;

	virtual void TickMatchState(const float DeltaTime) override;

	virtual void EndMatchState() override;
};
