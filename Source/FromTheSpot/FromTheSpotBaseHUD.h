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
	// Called when the match state changes
	virtual void MatchStateStarted(const EMatchState NewMatchState);
	
	// Called when the coin flip has been decided, passes in the data for the animation
	virtual void CoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);

	// Flips the players names
	virtual void FlipPlayerNames();
	
	// Updates the match data 
	virtual void UpdateMatchData(const FPlayerData& PlayerAData, const FPlayerData& PlayerBData);

	// Freezes / unfreezes the timing indicator
	virtual void FreezeIndicator(bool bFreeze);

	// Displays the penalty result
	virtual void PenaltyResult(const bool bScored, const FString& PlayerName);

	// Return the timing multiplier at the current moment 
	virtual float GetTimingMultiplier() const;

	// Resets the score circle images
	virtual void ClearScoreImages();

protected:
	// Reference to the match hud
	UPROPERTY(BlueprintReadWrite)
	UFromTheSpotMatchHUD* MatchHUD = nullptr;
};
