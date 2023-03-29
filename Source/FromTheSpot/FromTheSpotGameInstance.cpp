// Written by Lewis Heath.

#include "FromTheSpotGameInstance.h"

UFromTheSpotGameInstance::UFromTheSpotGameInstance()
{
	
}

void UFromTheSpotGameInstance::SetMatchData(const FMatchData& NewMatchData)
{
	MatchData = NewMatchData;
}

FMatchData UFromTheSpotGameInstance::GetMatchData() const
{
	return MatchData;
}
