// Written by Lewis Heath.

#include "FromTheSpotGameModeBase.h"

#include "Football.h"
#include "FootballGoal.h"
#include "FromTheSpotBaseHUD.h"
#include "FromTheSpotCharacter.h"
#include "FromTheSpotMatchStateAttack.h"
#include "FromTheSpotMatchStateCoinFlip.h"
#include "FromTheSpotMatchStateDefend.h"
#include "FromTheSpotMatchStateInteraction.h"
#include "FromTheSpotMatchStateResults.h"
#include "Goalkeeper.h"
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

	TArray<AActor*> FoundFootballs;
	UGameplayStatics::GetAllActorsOfClass(this, AFootball::StaticClass(), FoundFootballs);

	if (!FoundFootballs.IsValidIndex(0))
	{
		return;
	}

	MatchBall = Cast<AFootball>(FoundFootballs[0]);
	if (!IsValid(MatchBall))
	{
		return;
	}

	TArray<AActor*> FoundAttackers;
	UGameplayStatics::GetAllActorsOfClass(this, AFromTheSpotCharacter::StaticClass(), FoundAttackers);

	if (!FoundAttackers.IsValidIndex(0))
	{
		return;
	}

	MatchAttacker = Cast<AFromTheSpotCharacter>(FoundAttackers[0]);
	if (!IsValid(MatchAttacker))
	{
		return;
	}

	TArray<AActor*> FoundGoalkeepers;
	UGameplayStatics::GetAllActorsOfClass(this, AGoalkeeper::StaticClass(), FoundGoalkeepers);

	if (!FoundGoalkeepers.IsValidIndex(0))
	{
		return;
	}

	MatchGoalkeeper = Cast<AGoalkeeper>(FoundGoalkeepers[0]);
	if (!IsValid(MatchGoalkeeper))
	{
		return;
	}

	TArray<AActor*> FoundGoals;
	UGameplayStatics::GetAllActorsOfClass(this, AFootballGoal::StaticClass(), FoundGoals);

	if (!FoundGoals.IsValidIndex(0))
	{
		return;
	}

	MatchGoal = Cast<AFootballGoal>(FoundGoals[0]);
	if (!IsValid(MatchGoal))
	{
		return;
	}

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

			case EMatchState::DEFEND:
			{
				UFromTheSpotMatchStateDefend* DefendStateObject = NewObject<UFromTheSpotMatchStateDefend>(this);
				if (IsValid(DefendStateObject))
				{
					CreatedMatchState = DefendStateObject;
				}
				
				break;
			}
			
			case EMatchState::INTERACTION:
			{
				UFromTheSpotMatchStateInteraction* InteractionStateObject = NewObject<UFromTheSpotMatchStateInteraction>(this);
				if (IsValid(InteractionStateObject))
				{
					CreatedMatchState = InteractionStateObject;
				}
			
				break;
			}

			case EMatchState::RESULTS:
			{
				UFromTheSpotMatchStateResults* ResultsStateObject = NewObject<UFromTheSpotMatchStateResults>(this);
				if (IsValid(ResultsStateObject))
				{
					CreatedMatchState = ResultsStateObject;
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

	if (CurrentMatchStateInfo.Type == EMatchState::INTERACTION)
	{
		CheckEndMatch();
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
	const FMatchStateData& ResultsMatchStateData = MatchStateInfo[MatchStateInfo.Num()-1];
	StartMatchState(ResultsMatchStateData);
	HUDUpdateMatchData(PlayerAData, PlayerBData);
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
	
	if (bPlayer1Heads && !bPlayer2Heads)
	{
		if (CoinFlipResult == ECoinFlipResult::HEADS)
		{
			StartingPlayerName = "Player 1";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 1");
		}
		else
		{
			StartingPlayerName = "Player 2";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 2");
		}
	}
	
	if (!bPlayer1Heads && bPlayer2Heads)
	{
		if (CoinFlipResult == ECoinFlipResult::HEADS)
		{
			StartingPlayerName = "Player 2";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 2");
		}
		else
		{
			StartingPlayerName = "Player 1";
			HUDCoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, "Player 1");
		}
	}

	AttackingPlayerName = StartingPlayerName;

	PlayerAData.Name = "Player 1";
	PlayerBData.Name = "Player 2";
}

void AFromTheSpotGameModeBase::UpdateMatchData(const FPlayerData& NewPlayerAData,
	const FPlayerData& NewPlayerBData)
{
	PlayerAData = NewPlayerAData;
	PlayerBData = NewPlayerBData;

	HUDUpdateMatchData(PlayerAData, PlayerBData);
}

void AFromTheSpotGameModeBase::SetAttackInformation(const FVector NewShotLocation, const float NewTimingMultiplier)
{
	ShotLocation = NewShotLocation;
	TimingMultiplier = NewTimingMultiplier;

	StartNextMatchState();
}

void AFromTheSpotGameModeBase::SetDefendInformation(const FVector NewSaveLocation)
{
	SaveLocation = NewSaveLocation;

	StartNextMatchState();
}

void AFromTheSpotGameModeBase::BlowWhistle()
{
	if (!IsValid(MatchAttacker))
	{
		return;
	}

	MatchAttacker->TakePenalty();
}

void AFromTheSpotGameModeBase::TakePenalty()
{
	if (!IsValid(MatchBall))
	{
		return;
	}

	if (!IsValid(MatchGoal))
	{
		return;
	}

	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	const FDivePointInfo DivePointInfo = MatchGoal->GetDiveInfo(SaveLocation);

	MatchGoalkeeper->BP_Dive(DivePointInfo);

	MatchBall->Shoot(ShotLocation, TimingMultiplier);

	World->GetTimerManager().SetTimer(PenaltyMissedTimerHandle, this, &AFromTheSpotGameModeBase::GoalMissed, MaxPenaltyShotTime);
	
	// tell goalkeeper to dive
}

void AFromTheSpotGameModeBase::GoalScored()
{
	if (bRoundDecided)
	{
		return;
	}
	
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}
	
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}
	
	if (AttackingPlayerName == PlayerAData.Name)
	{
		PlayerAData.PenaltiesTaken++;
		PlayerAData.Score++;
	}
	else if (AttackingPlayerName == PlayerBData.Name)
	{
		PlayerBData.PenaltiesTaken++;
		PlayerBData.Score++;
	}

	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, PenaltyMissedTimerHandle);
	PlayerMatchHUD->PenaltyResult(true, AttackingPlayerName);
	CurrentMatchState->ActivateRoundTimer(true);
	bRoundDecided = true;
}

void AFromTheSpotGameModeBase::GoalMissed()
{
	if (bRoundDecided)
	{
		return;
	}
	
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}
	
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	if (AttackingPlayerName == PlayerAData.Name)
	{
		PlayerAData.PenaltiesTaken++;
	}
	else if (AttackingPlayerName == PlayerBData.Name)
	{
		PlayerBData.PenaltiesTaken++;
	}

	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, PenaltyMissedTimerHandle);
	PlayerMatchHUD->PenaltyResult(false, AttackingPlayerName);
	CurrentMatchState->ActivateRoundTimer(true);
	bRoundDecided = true;
}

void AFromTheSpotGameModeBase::CheckEndMatch()
{
	bool bEndMatch = false;
	
	FPlayerData WinningPlayer = FPlayerData();
	
	const int PlayerAPenaltiesTaken = PlayerAData.PenaltiesTaken;
	const int PlayerBPenaltiesTaken = PlayerBData.PenaltiesTaken;

	if (!bSuddenDeath && PlayerAPenaltiesTaken == 5 && PlayerBPenaltiesTaken == 5)
	{
		bSuddenDeath = true;
	}
	
	const int PlayerAScore = PlayerAData.Score;
	const int PlayerBScore = PlayerBData.Score;

	if (!bSuddenDeath)
	{
		if (PlayerAScore > (PlayerBScore + (5 - PlayerBData.PenaltiesTaken)))
		{
			bEndMatch = true;
			WinningPlayer = PlayerAData;
		}
		else if (PlayerBScore > (PlayerAScore + (5 - PlayerAData.PenaltiesTaken)))
		{
			bEndMatch = true;
			WinningPlayer = PlayerBData;
		}
	}
	else
	{
		if (PlayerAPenaltiesTaken == PlayerBPenaltiesTaken)
		{
			if (PlayerAScore > PlayerBScore)
			{
				bEndMatch = true;
				WinningPlayer = PlayerAData;
			}
			else if (PlayerBScore > PlayerAScore)
			{
				bEndMatch = true;
				WinningPlayer = PlayerBData;
			}
		}
	}
	
	if (bEndMatch)
	{
		EndMatch();
	}
	else
	{
		if (bSuddenDeath && !bEndMatch && PlayerAPenaltiesTaken % 5 == 0 && PlayerBPenaltiesTaken % 5 == 0)
		{
			HUDClearScoreImages();
		}
		
		FlipPlayerNames();

		if (!IsValid(MatchBall) || !IsValid(MatchAttacker) || !IsValid(MatchGoalkeeper))
		{
			return;
		}

		MatchBall->ResetToStart();
		MatchAttacker->ResetToStart();
		MatchGoalkeeper->ResetToStart();
		
		bRoundDecided = false;
		CurrentMatchStateIndex = 0;
	}
}

void AFromTheSpotGameModeBase::FlipPlayerNames()
{
	if (AttackingPlayerName == PlayerAData.Name)
	{
		AttackingPlayerName = PlayerBData.Name;
	}
	else if (AttackingPlayerName == PlayerBData.Name)
	{
		AttackingPlayerName = PlayerAData.Name;
	}

	HUDFlipPlayerNames();
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

void AFromTheSpotGameModeBase::HUDFlipPlayerNames()
{
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->FlipPlayerNames();
}

void AFromTheSpotGameModeBase::HUDUpdateMatchData(const FPlayerData& NewPlayerAData, const FPlayerData& NewPlayerBData)
{
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->UpdateMatchData(NewPlayerAData, NewPlayerBData);
}

void AFromTheSpotGameModeBase::HUDClearScoreImages()
{
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->ClearScoreImages();
}
