// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FromTheSpotDataTypes.h"
#include "FromTheSpotGameModeBase.generated.h"

class UFromTheSpotMatchStateBase;
class AFromTheSpotBaseHUD;
class AFootball;
class AFromTheSpotCharacter;
class AGoalkeeper;
class AFootballGoal;

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

	UFUNCTION(BlueprintCallable)
	virtual void SetDefendInformation(const FVector NewSaveLocation);

	virtual void BlowWhistle();

	UFUNCTION(BlueprintCallable)
	virtual void TakePenalty();

	UFUNCTION(BlueprintCallable)
	virtual void GoalScored();

	UFUNCTION(BlueprintCallable)
	virtual void GoalMissed();

	virtual void CheckEndMatch();

	virtual void FlipPlayerNames();

	// HUD
	virtual void HUDMatchStateStarted(const EMatchState NewMatchState);
	
	virtual void HUDCoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);

	virtual void HUDFlipPlayerNames();

	virtual void HUDUpdateMatchData(const FPlayerData& NewPlayerAData, const FPlayerData& NewPlayerBData);

	virtual void HUDClearScoreImages();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMatchStateData> MatchStateInfo;

	UPROPERTY(BlueprintReadOnly)
	AFromTheSpotBaseHUD* PlayerMatchHUD = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AFootball* MatchBall = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AFromTheSpotCharacter* MatchAttacker = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AGoalkeeper* MatchGoalkeeper = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AFootballGoal* MatchGoal = nullptr;

	int CurrentMatchStateIndex = 0;
	
	FMatchStateData CurrentMatchStateInfo = FMatchStateData();

	// Match
	FPlayerData PlayerAData = FPlayerData();
	FPlayerData PlayerBData = FPlayerData();

	FString AttackingPlayerName = "";

	FVector ShotLocation = FVector::ZeroVector;
	float TimingMultiplier = 0.0f;

	FVector SaveLocation = FVector::ZeroVector;

	FTimerHandle PenaltyMissedTimerHandle;

	float MaxPenaltyShotTime = 3.0f;

	bool bRoundDecided = false;

	bool bSuddenDeath = false;
};
