// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FromTheSpotDataTypes.h"
#include "FromTheSpotMatchHUD.generated.h"

UCLASS()
class FROMTHESPOT_API UFromTheSpotMatchHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_MatchStateStarted(const EMatchState NewMatchState);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_CoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_FlipPlayerNames();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateMatchData(const FPlayerData& PlayerAData, const FPlayerData& PlayerBData);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_FreezeIndicator(bool bFreeze);

	float GetTimingMultiplier() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimingMultiplier = 0.0f;
};
