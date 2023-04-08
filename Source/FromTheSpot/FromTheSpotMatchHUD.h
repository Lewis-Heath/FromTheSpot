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
	// Blueprint event, called when the match state changes
	UFUNCTION(BlueprintImplementableEvent)
	void BP_MatchStateStarted(const EMatchState NewMatchState);

	// Blueprint event, passes in the data for the animation
	UFUNCTION(BlueprintImplementableEvent)
	void BP_CoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);

	// Blueprint event, flips the players names
	UFUNCTION(BlueprintImplementableEvent)
	void BP_FlipPlayerNames();

	// Blueprint event, updates the match data 
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateMatchData(const FPlayerData& PlayerAData, const FPlayerData& PlayerBData);

	// Blueprint event, freezes / unfreezes the timing indicator
	UFUNCTION(BlueprintImplementableEvent)
	void BP_FreezeIndicator(bool bFreeze);

	// Blueprint event, displays the penalty result
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PenaltyResult(const bool bScored, const FString& PlayerName);

	// Return the timing multiplier at the current moment 
	float GetTimingMultiplier() const;

	// Blueprint event, resets the score circle images
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ClearScoreImages();

protected:
	// The timing multiplier value based on the indicator position
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimingMultiplier = 0.0f;
};
