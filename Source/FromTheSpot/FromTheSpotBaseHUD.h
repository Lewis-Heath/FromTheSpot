// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotDataTypes.h"
#include "GameFramework/HUD.h"
#include "FromTheSpotBaseHUD.generated.h"

class UFromTheSpotMatchHUD;

UCLASS()
class FROMTHESPOT_API AFromTheSpotBaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	//
	virtual void MatchStateStarted(const EMatchState NewMatchState);
	
	//
	virtual void CoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);

protected:
	//
	UPROPERTY(BlueprintReadWrite)
	UFromTheSpotMatchHUD* MatchHUD = nullptr;
};
