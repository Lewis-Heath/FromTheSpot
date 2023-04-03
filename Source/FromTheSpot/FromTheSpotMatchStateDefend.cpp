// Written by Lewis Heath.

#include "FromTheSpotMatchStateDefend.h"

UFromTheSpotMatchStateDefend::UFromTheSpotMatchStateDefend()
{
	MatchStateType = EMatchState::DEFEND;
}

void UFromTheSpotMatchStateDefend::StartMatchState()
{
	Super::StartMatchState();
}

void UFromTheSpotMatchStateDefend::TickMatchState(const float DeltaTime)
{
	Super::TickMatchState(DeltaTime);
}

void UFromTheSpotMatchStateDefend::EndMatchState()
{
	Super::EndMatchState();
}


