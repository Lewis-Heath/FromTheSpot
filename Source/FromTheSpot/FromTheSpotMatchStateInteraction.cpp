// Written by Lewis Heath.

#include "FromTheSpotMatchStateInteraction.h"

#include "FromTheSpotGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

UFromTheSpotMatchStateInteraction::UFromTheSpotMatchStateInteraction()
{
	MatchStateType = EMatchState::INTERACTION;
}

void UFromTheSpotMatchStateInteraction::StartMatchState()
{
	// Set the timer off by default
	bTimerActive = false;

	// Grab the world check its valid
	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	// Set a whistle timer
	World->GetTimerManager().SetTimer(WhistleTimerHandle, this, &UFromTheSpotMatchStateInteraction::BlowWhistle, WhistleTime);
}

void UFromTheSpotMatchStateInteraction::EndMatchState()
{
	// Clear the whistle timer
	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, WhistleTimerHandle);
	Super::EndMatchState();
}

void UFromTheSpotMatchStateInteraction::BlowWhistle()
{
	// Check the game mode is valid
	if (!IsValid(GameModeReference))
	{
		return;
	}

	GameModeReference->BlowWhistle();
}
