// Written by Lewis Heath.

#include "FromTheSpotMatchStateBase.h"

UFromTheSpotMatchStateBase::UFromTheSpotMatchStateBase()
{
	
}

void UFromTheSpotMatchStateBase::StartMatchState()
{
	
}

void UFromTheSpotMatchStateBase::TickMatchState(const float DeltaTime)
{
	if (bTimerActive)
	{
		CurrentTimeInProgress += DeltaTime;
	}
}

void UFromTheSpotMatchStateBase::EndMatchState()
{
	
}

void UFromTheSpotMatchStateBase::SetGameModeReference(AFromTheSpotGameModeBase* NewGameModeReference)
{
	GameModeReference = NewGameModeReference;
}

void UFromTheSpotMatchStateBase::SetMaxTimeInProgress(const float NewMaxTime)
{
	MaxTimeInProgress = NewMaxTime;
}

float UFromTheSpotMatchStateBase::GetMaxTimeInProgress() const
{
	return MaxTimeInProgress;
}

float UFromTheSpotMatchStateBase::GetCurrentTimeInProgress() const
{
	return CurrentTimeInProgress;
}

void UFromTheSpotMatchStateBase::ActivateRoundTimer(const bool bActive)
{
	bTimerActive = bActive;
}
