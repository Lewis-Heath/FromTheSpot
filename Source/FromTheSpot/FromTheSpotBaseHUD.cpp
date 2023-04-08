// Written by Lewis Heath.

#include "FromTheSpotBaseHUD.h"
#include "FromTheSpotMatchHUD.h"

void AFromTheSpotBaseHUD::MatchStateStarted(const EMatchState NewMatchState)
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_MatchStateStarted(NewMatchState);
}

void AFromTheSpotBaseHUD::CoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads,
                                          const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName)
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_CoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, StartingPlayerName);
}

void AFromTheSpotBaseHUD::FlipPlayerNames()
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_FlipPlayerNames();
}

void AFromTheSpotBaseHUD::UpdateMatchData(const FPlayerData& PlayerAData, const FPlayerData& PlayerBData)
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_UpdateMatchData(PlayerAData, PlayerBData);
}

void AFromTheSpotBaseHUD::FreezeIndicator(bool bFreeze)
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_FreezeIndicator(bFreeze);
}

void AFromTheSpotBaseHUD::PenaltyResult(const bool bScored, const FString& PlayerName)
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_PenaltyResult(bScored, PlayerName);
}

float AFromTheSpotBaseHUD::GetTimingMultiplier() const
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return 0.0f;
	}

	return MatchHUD->GetTimingMultiplier();
}

void AFromTheSpotBaseHUD::ClearScoreImages()
{
	// Check the match hud is valid
	if (!IsValid(MatchHUD))
	{
		return;
	}

	MatchHUD->BP_ClearScoreImages();
}
