// Written by Lewis Heath.

#include "FromTheSpotBaseHUD.h"
#include "FromTheSpotMatchHUD.h"

void AFromTheSpotBaseHUD::MatchStateStarted(const EMatchState NewMatchState)
{
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_MatchStateStarted(NewMatchState);
}

void AFromTheSpotBaseHUD::CoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads,
                                          const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName)
{
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_CoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, StartingPlayerName);
}
