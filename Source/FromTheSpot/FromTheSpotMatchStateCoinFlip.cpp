// Written by Lewis Heath.

#include "FromTheSpotMatchStateCoinFlip.h"
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
	}
}

void UFromTheSpotMatchStateCoinFlip::EndMatchState()
{
	Super::EndMatchState();
}
