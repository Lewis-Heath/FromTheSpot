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
	// Sets default values for this actor's properties
	AFromTheSpotGameModeBase();

	// Starts the next match state in the array
	virtual void StartNextMatchState();

	// Starts the next match state based on the info passed in
	virtual void StartMatchState(const FMatchStateData& NewMatchStateInfo);

	// Check if the current match state should be ended based of time
	virtual void CheckEndCurrentMatchState();

	// Ends the match, starts the post match state
	virtual void EndMatch();

	// Holds the coin flip info, updates the necessary data
	virtual void CoinFlipDecided(const ECoinFlipResult CoinFlipResult, bool bFlipPlayers);

	// Updates the players data for the current match
	virtual void UpdateMatchData(const FPlayerData& NewPlayerAData, const FPlayerData& NewPlayerBData);

	// Sets the attack information for the attacking turn
	UFUNCTION(BlueprintCallable)
	virtual void SetAttackInformation(const FVector NewShotLocation, const float NewTimingMultiplier);

	// Returns the cached attack shot location
	UFUNCTION(BlueprintCallable)
	virtual FVector GetShotLocation() const;

	// Sets the defend information for the defending turn
	UFUNCTION(BlueprintCallable)
	virtual void SetDefendInformation(const FVector NewSaveLocation);

	// Starts the penalty interaction 
	virtual void BlowWhistle();

	// Hits the ball, tells the goalkeeper to dive
	UFUNCTION(BlueprintCallable)
	virtual void TakePenalty();

	// Updates the hud and params for when a penalty is scored
	UFUNCTION(BlueprintCallable)
	virtual void GoalScored();

	// Updates the hud and params for when a penalty is missed
	UFUNCTION(BlueprintCallable)
	virtual void GoalMissed();

	// Checks if the match should end, ends if needed
	virtual void CheckEndMatch();

	// Flips the attacking player name round
	virtual void FlipPlayerNames();

	// Returns the current game mode type
	UFUNCTION(BlueprintCallable)
	virtual EGameModeType GetGameModeType() const;

	// Hud functions
	virtual void HUDMatchStateStarted(const EMatchState NewMatchState);
	virtual void HUDCoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);
	virtual void HUDFlipPlayerNames();
	virtual void HUDUpdateMatchData(const FPlayerData& NewPlayerAData, const FPlayerData& NewPlayerBData);
	virtual void HUDClearScoreImages();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function called every frame on this Actor
	virtual void Tick(float DeltaSeconds) override;

	// Array holding the different match states for this game mode
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMatchStateData> MatchStateInfo;

	// The current match state index
	int CurrentMatchStateIndex = 0;

	// The current match state info
	FMatchStateData CurrentMatchStateInfo = FMatchStateData();

	// Reference to the players match hud
	UPROPERTY(BlueprintReadOnly)
	AFromTheSpotBaseHUD* PlayerMatchHUD = nullptr;

	// Reference to the match ball
	UPROPERTY(BlueprintReadOnly)
	AFootball* MatchBall = nullptr;

	// Reference to the match attacker
	UPROPERTY(BlueprintReadOnly)
	AFromTheSpotCharacter* MatchAttacker = nullptr;

	// Reference to the match goalkeeper
	UPROPERTY(BlueprintReadOnly)
	AGoalkeeper* MatchGoalkeeper = nullptr;

	// Reference to the match goal
	UPROPERTY(BlueprintReadOnly)
	AFootballGoal* MatchGoal = nullptr;

	// The player data for this match
	FPlayerData PlayerAData = FPlayerData();
	FPlayerData PlayerBData = FPlayerData();

	// The current attacking players name
	FString AttackingPlayerName = "";

	// The shot location the player will strike the ball towards for the current attack turn
	FVector ShotLocation = FVector::ZeroVector;

	// The timing multiplier for the current attack turn
	float TimingMultiplier = 0.0f;

	// The save location the goalkeeper will dive towards for the current defend turn
	FVector SaveLocation = FVector::ZeroVector;

	// Penalty missed timer activated when the ball is hit
	FTimerHandle PenaltyMissedTimerHandle;

	// The max amount of time the users must wait before a penalty is deemed as a miss
	float MaxPenaltyShotTime = 3.0f;

	// Has the current round been decided 
	bool bRoundDecided = false;

	// Is the match in sudden death
	bool bSuddenDeath = false;

	// The type of game mode
	EGameModeType GameModeType = EGameModeType::NONE;
};
