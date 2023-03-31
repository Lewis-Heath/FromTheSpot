// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotMatchStateBase.h"
#include "FromTheSpotMatchStateAttack.generated.h"

UCLASS()
class FROMTHESPOT_API UFromTheSpotMatchStateAttack : public UFromTheSpotMatchStateBase
{
	GENERATED_BODY()

public:
	UFromTheSpotMatchStateAttack();

	virtual void StartMatchState() override;

	virtual void TickMatchState(const float DeltaTime) override;

	virtual void EndMatchState() override;
};
