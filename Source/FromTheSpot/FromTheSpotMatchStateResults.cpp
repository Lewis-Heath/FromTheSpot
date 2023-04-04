// Written by Lewis Heath.

#include "FromTheSpotMatchStateResults.h"

UFromTheSpotMatchStateResults::UFromTheSpotMatchStateResults()
{
	MatchStateType = EMatchState::RESULTS;
}

void UFromTheSpotMatchStateResults::StartMatchState()
{
	Super::StartMatchState();
}

void UFromTheSpotMatchStateResults::TickMatchState(const float DeltaTime)
{
	Super::TickMatchState(DeltaTime);
}

void UFromTheSpotMatchStateResults::EndMatchState()
{
	Super::EndMatchState();
}
