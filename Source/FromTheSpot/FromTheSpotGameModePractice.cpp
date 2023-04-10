// Written by Lewis Heath.

#include "FromTheSpotGameModePractice.h"

AFromTheSpotGameModePractice::AFromTheSpotGameModePractice()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set the game mode type
	GameModeType = EGameModeType::PRACTICE;
}

void AFromTheSpotGameModePractice::CoinFlipDecided(const ECoinFlipResult CoinFlipResult, bool bFlipPlayers)
{
	// Set the bool variables
	bool bPlayer1Heads = true;
	bool bPlayer2Heads = false;

	// Flip the players if needed
	if (bFlipPlayers)
	{
		bPlayer1Heads = false;
		bPlayer2Heads = true;
	}
	
	FString StartingPlayerName = "";

	// If player 1 is heads and player 2 is tails
	if (bPlayer1Heads && !bPlayer2Heads)
	{
		if (CoinFlipResult == ECoinFlipResult::HEADS)
		{
			StartingPlayerName = "Player 1";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 1");
		}
		else
		{
			StartingPlayerName = "AI";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "AI");
		}
	}

	// If player 2 is heads and player 1 is tails
	if (!bPlayer1Heads && bPlayer2Heads)
	{
		if (CoinFlipResult == ECoinFlipResult::HEADS)
		{
			StartingPlayerName = "AI";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "AI");
		}
		else
		{
			StartingPlayerName = "Player 1";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 1");
		}
	}

	// Set the attacking player name
	AttackingPlayerName = StartingPlayerName;

	// Set the player data names
	PlayerAData.Name = "Player 1";
	PlayerBData.Name = "AI";
}
