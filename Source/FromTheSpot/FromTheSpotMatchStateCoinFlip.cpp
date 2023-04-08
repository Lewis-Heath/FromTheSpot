// Written by Lewis Heath.

#include "FromTheSpotMatchStateCoinFlip.h"

#include "FromTheSpotGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FromTheSpotGameModeBase.h"

UFromTheSpotMatchStateCoinFlip::UFromTheSpotMatchStateCoinFlip()
{
	MatchStateType = EMatchState::COIN_FLIP;
}

void UFromTheSpotMatchStateCoinFlip::TickMatchState(const float DeltaTime)
{
	Super::TickMatchState(DeltaTime);

	// If the coin result is undecided and the sufficient time has passed
	if (CoinFlipResult == ECoinFlipResult::NONE && CurrentTimeInProgress >= CoinFlipDecisionTime)
	{
		// Check the game mode is valid
		if (!IsValid(GameModeReference))
		{
			return;	
		}

		// Get a random bool for heads or tails
		const bool bHeads = UKismetMathLibrary::RandomBool();

		// Set the coin flip result
		if (bHeads)
		{
			CoinFlipResult = ECoinFlipResult::HEADS;
		}
		else
		{
			CoinFlipResult = ECoinFlipResult::TAILS;
		}

		// Get a random bool to flip the players coin side
		const bool bFlipPlayers = UKismetMathLibrary::RandomBool();

		// Update the game mode
		GameModeReference->CoinFlipDecided(CoinFlipResult, bFlipPlayers);

		// Grab the game instance, check its valid
		const UFromTheSpotGameInstance* GameInstance = Cast<UFromTheSpotGameInstance>(GameModeReference->GetGameInstance());
		if (!IsValid(GameInstance))
		{
			return;
		}

		// Get the match data
		const FMatchData MatchData = GameInstance->GetMatchData();

		// Set player A data up
		FString PlayerATeamName = "Grey Team";
		FPlayerData PlayerAData = FPlayerData();
		PlayerAData.Name = "Player 1";

		const FString PlayerATeamDataName = MatchData.Player1TeamData.Name;
		if (PlayerATeamDataName.Len() > 0)
		{
			PlayerATeamName = PlayerATeamDataName;
		}
		
		PlayerAData.TeamName = PlayerATeamName;
		PlayerAData.TeamBadge = MatchData.Player1TeamData.Badge;
		PlayerAData.Difficulty = MatchData.Player1Difficulty;

		// Set player B data up
		FString PlayerBTeamName = "White Team";
		FPlayerData PlayerBData = FPlayerData();
		PlayerBData.Name = "Player 2";

		const FString PlayerBTeamDataName = MatchData.Player2TeamData.Name;
		if (PlayerBTeamDataName.Len() > 0)
		{
			PlayerBTeamName = PlayerBTeamDataName;
		}
		
		PlayerBData.TeamName = PlayerBTeamName;
		PlayerBData.TeamBadge = MatchData.Player2TeamData.Badge;
		PlayerBData.Difficulty = MatchData.Player2Difficulty;

		// Update the game mode
		GameModeReference->UpdateMatchData(PlayerAData, PlayerBData);
	}
}
