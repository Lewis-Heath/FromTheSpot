// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotGameModeBase.h"
#include "FromTheSpotGameModePractice.generated.h"

UCLASS()
class FROMTHESPOT_API AFromTheSpotGameModePractice : public AFromTheSpotGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFromTheSpotGameModePractice();
	
	// Holds the coin flip info, updates the necessary data, overridden 
	virtual void CoinFlipDecided(const ECoinFlipResult CoinFlipResult, bool bFlipPlayers) override;
};
