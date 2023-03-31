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

void UFromTheSpotMatchStateCoinFlip::StartMatchState()
{
	Super::StartMatchState();
}

void UFromTheSpotMatchStateCoinFlip::TickMatchState(const float DeltaTime)
{
	Super::TickMatchState(DeltaTime);

	if (CoinFlipResult == ECoinFlipResult::NONE && CurrentTimeInProgress >= CoinFlipDecisionTime)
	{
		if (!IsValid(GameModeReference))
		{
			return;	
		}

		const bool bHeads = UKismetMathLibrary::RandomBool();

		if (bHeads)
		{
			CoinFlipResult = ECoinFlipResult::HEADS;
		}
		else
		{
			CoinFlipResult = ECoinFlipResult::TAILS;
		}

		const bool bFlipPlayers = UKismetMathLibrary::RandomBool();

		GameModeReference->CoinFlipDecided(CoinFlipResult, bFlipPlayers);

		const UFromTheSpotGameInstance* GameInstance = Cast<UFromTheSpotGameInstance>(GameModeReference->GetGameInstance());
		if (!IsValid(GameInstance))
		{
			return;
		}

		const FMatchData MatchData = GameInstance->GetMatchData();

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
	
		GameModeReference->UpdateMatchData(PlayerAData, PlayerBData);
	}
}

void UFromTheSpotMatchStateCoinFlip::EndMatchState()
{
	Super::EndMatchState();
}
