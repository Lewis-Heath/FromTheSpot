// Written by Lewis Heath.

#include "FromTheSpotMatchStateAttack.h"

UFromTheSpotMatchStateAttack::UFromTheSpotMatchStateAttack()
{
	MatchStateType = EMatchState::ATTACK;
}

void UFromTheSpotMatchStateAttack::StartMatchState()
{
	Super::StartMatchState();
}

void UFromTheSpotMatchStateAttack::TickMatchState(const float DeltaTime)
{
	Super::TickMatchState(DeltaTime);
}

void UFromTheSpotMatchStateAttack::EndMatchState()
{
	Super::EndMatchState();
}
