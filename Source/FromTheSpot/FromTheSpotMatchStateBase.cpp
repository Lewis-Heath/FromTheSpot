// Written by Lewis Heath.

#include "FromTheSpotMatchStateBase.h"

UFromTheSpotMatchStateBase::UFromTheSpotMatchStateBase()
{
	
}

void UFromTheSpotMatchStateBase::StartMatchState()
{
	// Set the timer to active
	bTimerActive = true;
}

void UFromTheSpotMatchStateBase::TickMatchState(const float DeltaTime)
{
	// Is the timer active
	if (bTimerActive)
	{
		// Increase the progress float
		CurrentTimeInProgress += DeltaTime;
	}
}

void UFromTheSpotMatchStateBase::EndMatchState()
{
	// Reset the time in progress, flip the timer bool
	CurrentTimeInProgress = 0.0f;
	bTimerActive = false;
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
