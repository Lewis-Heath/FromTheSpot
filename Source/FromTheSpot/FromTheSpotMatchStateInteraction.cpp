// Written by Lewis Heath.

#include "FromTheSpotMatchStateInteraction.h"

#include "FromTheSpotGameModeBase.h"

UFromTheSpotMatchStateInteraction::UFromTheSpotMatchStateInteraction()
{
	MatchStateType = EMatchState::INTERACTION;
	bTimerActive = false;
}

void UFromTheSpotMatchStateInteraction::StartMatchState()
{
	Super::StartMatchState();

	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	World->GetTimerManager().SetTimer(WhistleTimerHandle, this, &UFromTheSpotMatchStateInteraction::BlowWhistle, WhistleTime);
	World->GetTimerManager().SetTimer(KickBallTimerHandle, this, &UFromTheSpotMatchStateInteraction::TakePenalty, KickBallTime);
}

void UFromTheSpotMatchStateInteraction::TickMatchState(const float DeltaTime)
{
	Super::TickMatchState(DeltaTime);
}

void UFromTheSpotMatchStateInteraction::EndMatchState()
{
	Super::EndMatchState();
}

void UFromTheSpotMatchStateInteraction::BlowWhistle()
{
	if (!IsValid(GameModeReference))
	{
		return;
	}

	GameModeReference->BlowWhistle();
}

void UFromTheSpotMatchStateInteraction::TakePenalty()
{
	if (!IsValid(GameModeReference))
	{
		return;
	}

	GameModeReference->TakePenalty();
}
