// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FromTheSpotDataTypes.h"
#include "FromTheSpotGameModeBase.generated.h"

class UFromTheSpotMatchStateBase;
class AFromTheSpotBaseHUD;

UCLASS()
class FROMTHESPOT_API AFromTheSpotGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFromTheSpotGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void StartNextMatchState();

	virtual void StartMatchState(const FMatchStateData& NewMatchStateInfo);

	virtual void CheckEndCurrentMatchState();

	virtual void EndMatch();

	virtual void CoinFlipDecided(const ECoinFlipResult CoinFlipResult, bool bFlipPlayers);

	virtual void UpdateMatchData(const FPlayerData& NewPlayerAData, const FPlayerData& NewPlayerBData);

	UFUNCTION(BlueprintCallable)
	virtual void SetAttackInformation(const FVector NewShotLocation, const float NewTimingMultiplier);

	// HUD
	virtual void HUDMatchStateStarted(const EMatchState NewMatchState);
	
	virtual void HUDCoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);

	virtual void HUDFlipPlayerNames();

	virtual void HUDUpdateMatchData(const FPlayerData& NewPlayerAData, const FPlayerData& NewPlayerBData);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMatchStateData> MatchStateInfo;

	UPROPERTY(BlueprintReadOnly)
	AFromTheSpotBaseHUD* PlayerMatchHUD = nullptr;

	int CurrentMatchStateIndex = 0;
	
	FMatchStateData CurrentMatchStateInfo = FMatchStateData();

	// Match
	FPlayerData PlayerAData = FPlayerData();
	FPlayerData PlayerBData = FPlayerData();

	FVector ShotLocation = FVector::ZeroVector;
	float TimingMultiplier = 0.0f;
};

inline void AFromTheSpotGameModeBase::UpdateMatchData(const FPlayerData& NewPlayerAData,
	const FPlayerData& NewPlayerBData)
{
	PlayerAData = NewPlayerAData;
	PlayerBData = NewPlayerBData;

	HUDUpdateMatchData(PlayerAData, PlayerBData);
}
