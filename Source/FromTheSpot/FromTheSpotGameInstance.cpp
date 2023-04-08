// Written by Lewis Heath.

#include "FromTheSpotGameInstance.h"

UFromTheSpotGameInstance::UFromTheSpotGameInstance()
{
	MatchVolumes = {1.0f, 1.0f, 1.0f, 1.0f};
}

void UFromTheSpotGameInstance::SetMatchData(const FMatchData& NewMatchData)
{
	MatchData = NewMatchData;
}

FMatchData UFromTheSpotGameInstance::GetMatchData() const
{
	return MatchData;
}

void UFromTheSpotGameInstance::SetMatchVolumes(const TArray<float>& NewMatchVolumes)
{
	MatchVolumes = NewMatchVolumes;
}

TArray<float> UFromTheSpotGameInstance::GetMatchVolumes() const
{
	return MatchVolumes;
}

float UFromTheSpotGameInstance::GetVolumeMultiplier(const int TypeIndex) const
{
	float VolumeMultiplier = 0.0f;

	if (!MatchVolumes.IsValidIndex(TypeIndex))
	{
		return VolumeMultiplier;
	}

	VolumeMultiplier = MatchVolumes[TypeIndex];
	return VolumeMultiplier;
}
