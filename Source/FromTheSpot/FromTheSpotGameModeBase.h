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

	// HUD
	virtual void HUDMatchStateStarted(const EMatchState NewMatchState);
	
	virtual void HUDCoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads, const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMatchStateData> MatchStateInfo;

	UPROPERTY(BlueprintReadOnly)
	AFromTheSpotBaseHUD* PlayerMatchHUD = nullptr;

	int CurrentMatchStateIndex = 0;
	
	FMatchStateData CurrentMatchStateInfo = FMatchStateData();

	// Match
	FString PlayerAName = "";
	FString PlayerBName = "";
};
