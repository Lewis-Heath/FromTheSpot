// Written by Lewis Heath.

#include "FromTheSpotGameModeBase.h"

#include "FromTheSpotBaseHUD.h"
#include "FromTheSpotMatchStateAttack.h"
#include "FromTheSpotMatchStateCoinFlip.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AFromTheSpotGameModeBase::AFromTheSpotGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFromTheSpotGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	AHUD* PlayerHUD = PlayerController->GetHUD();
	if (!IsValid(PlayerHUD))
	{
		return;
	}

	PlayerMatchHUD = Cast<AFromTheSpotBaseHUD>(PlayerHUD);
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	for (FMatchStateData& MatchStateData : MatchStateInfo)
	{
		UFromTheSpotMatchStateBase* CreatedMatchState = nullptr;
		
		switch (MatchStateData.Type)
		{
			case EMatchState::COIN_FLIP:
			{
				UFromTheSpotMatchStateCoinFlip* CoinFlipStateObject = NewObject<UFromTheSpotMatchStateCoinFlip>(this);
				if (IsValid(CoinFlipStateObject))
				{
					CreatedMatchState = CoinFlipStateObject;
				}
					
				break;
			}
			
			case EMatchState::ATTACK:
			{
				UFromTheSpotMatchStateAttack* AttackStateObject = NewObject<UFromTheSpotMatchStateAttack>(this);
				if (IsValid(AttackStateObject))
				{
					CreatedMatchState = AttackStateObject;
				}
					
				break;
			}
		}

		if (IsValid(CreatedMatchState))
		{
			MatchStateData.ClassReference = CreatedMatchState;
			CreatedMatchState->SetGameModeReference(this);
			CreatedMatchState->SetMaxTimeInProgress(MatchStateData.Time);
		}
	}
	
	if (!MatchStateInfo.IsValidIndex(0))
	{
		return;
	}

	const FMatchStateData StartingMatchStateData = MatchStateInfo[0];
	
	if (!IsValid(StartingMatchStateData.ClassReference))
	{
		return;
	}

	StartMatchState(StartingMatchStateData);
}

void AFromTheSpotGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	CurrentMatchState->TickMatchState(DeltaSeconds);

	CheckEndCurrentMatchState();
}

void AFromTheSpotGameModeBase::StartNextMatchState()
{
	const UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}
	
	CurrentMatchStateIndex++;

	if (CurrentMatchStateIndex >= MatchStateInfo.Num() || !MatchStateInfo.IsValidIndex(CurrentMatchStateIndex))
	{
		EndMatch();
	}
	else
	{
		const FMatchStateData& NewMatchStateData = MatchStateInfo[CurrentMatchStateIndex];
		StartMatchState(NewMatchStateData);
	}
}

void AFromTheSpotGameModeBase::StartMatchState(const FMatchStateData& NewMatchStateInfo)
{
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (IsValid(CurrentMatchState))
	{
		CurrentMatchState->EndMatchState();
	}
	
	if (!IsValid(NewMatchStateInfo.ClassReference))
	{
		return;
	}

	CurrentMatchStateInfo = NewMatchStateInfo;

	UFromTheSpotMatchStateBase* NewMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(NewMatchState))
	{
		return;
	}

	NewMatchState->StartMatchState();
	HUDMatchStateStarted(CurrentMatchStateInfo.Type);
}

void AFromTheSpotGameModeBase::CheckEndCurrentMatchState()
{
	const UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	const float MaxMatchStateTime = CurrentMatchState->GetMaxTimeInProgress();
	if (MaxMatchStateTime == -1.0f)
	{
		return;
	}
	
	const float CurrentMatchStateTime = CurrentMatchState->GetCurrentTimeInProgress();
	
	if (CurrentMatchStateTime >= MaxMatchStateTime)
	{
		StartNextMatchState();
	}
}

void AFromTheSpotGameModeBase::EndMatch()
{
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	CurrentMatchState->EndMatchState();
	CurrentMatchStateInfo = FMatchStateData();
	
	UKismetSystemLibrary::PrintString(GetWorld(), "MATCH ENDED", true, false, FColor::Red, 25.0f);
}

void AFromTheSpotGameModeBase::CoinFlipDecided(const ECoinFlipResult CoinFlipResult, bool bFlipPlayers)
{
	bool bPlayer1Heads = true;
	bool bPlayer2Heads = false;

	if (bFlipPlayers)
	{
		bPlayer1Heads = false;
		bPlayer2Heads = true;
	}

	FString StartingPlayerName = "";
	FString SecondPlayerName = "";
	
	if (bPlayer1Heads && !bPlayer2Heads)
	{
		if (CoinFlipResult == ECoinFlipResult::HEADS)
		{
			StartingPlayerName = "Player 1";
			SecondPlayerName = "Player 2";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 1");
		}
		else
		{
			StartingPlayerName = "Player 2";
			SecondPlayerName = "Player 1";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 2");
		}
	}
	
	if (!bPlayer1Heads && bPlayer2Heads)
	{
		if (CoinFlipResult == ECoinFlipResult::HEADS)
		{
			StartingPlayerName = "Player 2";
			SecondPlayerName = "Player 1";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 2");
		}
		else
		{
			StartingPlayerName = "Player 1";
			SecondPlayerName = "Player 2";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 1");
		}
	}

	PlayerAName = StartingPlayerName;
	PlayerBName = SecondPlayerName;
}

void AFromTheSpotGameModeBase::HUDMatchStateStarted(const EMatchState NewMatchState)
{
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->MatchStateStarted(NewMatchState);
}

void AFromTheSpotGameModeBase::HUDCoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads,
                                                  const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName)
{
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->CoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, StartingPlayerName);
}
