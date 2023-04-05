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
	bTimerActive = false;

	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	World->GetTimerManager().SetTimer(WhistleTimerHandle, this, &UFromTheSpotMatchStateInteraction::BlowWhistle, WhistleTime);
}

void UFromTheSpotMatchStateInteraction::TickMatchState(const float DeltaTime)
{
	Super::TickMatchState(DeltaTime);
}

void UFromTheSpotMatchStateInteraction::EndMatchState()
{
	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, WhistleTimerHandle);
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
