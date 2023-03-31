// Written by Lewis Heath.

#include "FromTheSpotMatchStateBase.h"

#include "Kismet/KismetSystemLibrary.h"

UFromTheSpotMatchStateBase::UFromTheSpotMatchStateBase()
{
	
}

void UFromTheSpotMatchStateBase::StartMatchState()
{
	//UKismetSystemLibrary::PrintString(GetWorld(), "Start Match State BASE", true, false, FColor::Green, 5.0f);
}

void UFromTheSpotMatchStateBase::TickMatchState(const float DeltaTime)
{
	CurrentTimeInProgress += DeltaTime;
	//UKismetSystemLibrary::PrintString(GetWorld(), "Tick BASE", true, false, FColor::Red, 0.0f);
}

void UFromTheSpotMatchStateBase::EndMatchState()
{
	//UKismetSystemLibrary::PrintString(GetWorld(), "End Match State BASE", true, false, FColor::Red, 5.0f);
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
