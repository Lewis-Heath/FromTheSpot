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

	// Set the default game mode type to classic
	GameModeType = EGameModeType::CLASSIC;
}

void AFromTheSpotGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Grabs all the footballs in the scene
	TArray<AActor*> FoundFootballs;
	UGameplayStatics::GetAllActorsOfClass(this, AFootball::StaticClass(), FoundFootballs);

	// Checks the index is valid
	if (!FoundFootballs.IsValidIndex(0))
	{
		return;
	}

	// Checks the ball is valid
	MatchBall = Cast<AFootball>(FoundFootballs[0]);
	if (!IsValid(MatchBall))
	{
		return;
	}

	// Grabs all the attackers in the scene
	TArray<AActor*> FoundAttackers;
	UGameplayStatics::GetAllActorsOfClass(this, AFromTheSpotCharacter::StaticClass(), FoundAttackers);

	// Checks the index is valid
	if (!FoundAttackers.IsValidIndex(0))
	{
		return;
	}

	// Checks the attacker is valid
	MatchAttacker = Cast<AFromTheSpotCharacter>(FoundAttackers[0]);
	if (!IsValid(MatchAttacker))
	{
		return;
	}

	// Grabs all the goalkeepers in the scene 
	TArray<AActor*> FoundGoalkeepers;
	UGameplayStatics::GetAllActorsOfClass(this, AGoalkeeper::StaticClass(), FoundGoalkeepers);

	// Checks the index is valid
	if (!FoundGoalkeepers.IsValidIndex(0))
	{
		return;
	}

	// Checks the goalkeeper is valid
	MatchGoalkeeper = Cast<AGoalkeeper>(FoundGoalkeepers[0]);
	if (!IsValid(MatchGoalkeeper))
	{
		return;
	}

	// Grabs all the goals in the scene
	TArray<AActor*> FoundGoals;
	UGameplayStatics::GetAllActorsOfClass(this, AFootballGoal::StaticClass(), FoundGoals);

	// Checks the index is valid
	if (!FoundGoals.IsValidIndex(0))
	{
		return;
	}

	// Checks the goal is valid
	MatchGoal = Cast<AFootballGoal>(FoundGoals[0]);
	if (!IsValid(MatchGoal))
	{
		return;
	}

	// Grabs the player controller, check its valid
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	// Grab the player hud, check its valid
	AHUD* PlayerHUD = PlayerController->GetHUD();
	if (!IsValid(PlayerHUD))
	{
		return;
	}

	// Grab the player match hud, check its valid
	PlayerMatchHUD = Cast<AFromTheSpotBaseHUD>(PlayerHUD);
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	// Loop through each match state in the array, creates an instance for each state
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

		// Check the created state is valid
		if (IsValid(CreatedMatchState))
		{
			// Set the class reference 
			MatchStateData.ClassReference = CreatedMatchState;

			// Set the max time and game mode for the state
			CreatedMatchState->SetGameModeReference(this);
			CreatedMatchState->SetMaxTimeInProgress(MatchStateData.Time);
		}
	}

	// Check the starting index is valid
	if (!MatchStateInfo.IsValidIndex(0))
	{
		return;
	}

	// Grab the starting match state data
	const FMatchStateData StartingMatchStateData = MatchStateInfo[0];

	// Check the class reference is valid 
	if (!IsValid(StartingMatchStateData.ClassReference))
	{
		return;
	}

	// Start the first match state
	StartMatchState(StartingMatchStateData);
}

void AFromTheSpotGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Grab the current match state, check its valid
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	// Tick the current match state
	CurrentMatchState->TickMatchState(DeltaSeconds);

	// Check if the current match state should end
	CheckEndCurrentMatchState();
}

void AFromTheSpotGameModeBase::StartNextMatchState()
{
	// Grab the current match state, check its valid
	const UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	// If the current state is interaction check if the game should end depending on score
	if (CurrentMatchStateInfo.Type == EMatchState::INTERACTION)
	{
		CheckEndMatch();
	}

	// Increase the state index
	CurrentMatchStateIndex++;

	// Check the index is valid
	if (CurrentMatchStateIndex >= MatchStateInfo.Num() || !MatchStateInfo.IsValidIndex(CurrentMatchStateIndex))
	{
		// End the match
		EndMatch();
	}
	else
	{
		// Grab the new match state data and start the match state
		const FMatchStateData& NewMatchStateData = MatchStateInfo[CurrentMatchStateIndex];
		StartMatchState(NewMatchStateData);
	}
}

void AFromTheSpotGameModeBase::StartMatchState(const FMatchStateData& NewMatchStateInfo)
{
	// Grab the current match state, check its valid
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (IsValid(CurrentMatchState))
	{
		// End the current match state
		CurrentMatchState->EndMatchState();
	}

	// Check if the new match state class is valid
	if (!IsValid(NewMatchStateInfo.ClassReference))
	{
		return;
	}

	// Update the current match state info
	CurrentMatchStateInfo = NewMatchStateInfo;

	// Check if the new match state class isa valid
	UFromTheSpotMatchStateBase* NewMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(NewMatchState))
	{
		return;
	}

	// Tell the match state its started and tell the HUD
	NewMatchState->StartMatchState();
	HUDMatchStateStarted(CurrentMatchStateInfo.Type);
}

void AFromTheSpotGameModeBase::CheckEndCurrentMatchState()
{
	// Grab the current match state, check its valid
	const UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	// Get the max time the state can be 
	const float MaxMatchStateTime = CurrentMatchState->GetMaxTimeInProgress();

	// If its -1 return - the state can stay 
	if (MaxMatchStateTime == -1.0f)
	{
		return;
	}

	// Get the current elapsed state time
	const float CurrentMatchStateTime = CurrentMatchState->GetCurrentTimeInProgress();

	// Check if the time is up
	if (CurrentMatchStateTime >= MaxMatchStateTime)
	{
		// Start the next match state
		StartNextMatchState();
	}
}

void AFromTheSpotGameModeBase::EndMatch()
{
	// Grab the post match state data from the end of the array, change the match state, notify the hud
	const FMatchStateData& ResultsMatchStateData = MatchStateInfo[MatchStateInfo.Num()-1];
	StartMatchState(ResultsMatchStateData);
	HUDUpdateMatchData(PlayerAData, PlayerBData);
}

void AFromTheSpotGameModeBase::CoinFlipDecided(const ECoinFlipResult CoinFlipResult, bool bFlipPlayers)
{
	// Set the bool variables
	bool bPlayer1Heads = true;
	bool bPlayer2Heads = false;

	// Flip the players if needed
	if (bFlipPlayers)
	{
		bPlayer1Heads = false;
		bPlayer2Heads = true;
	}
	
	FString StartingPlayerName = "";

	// If player 1 is heads and player 2 is tails
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

	// If player 2 is heads and player 1 is tails
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

	// Set the attacking player name
	AttackingPlayerName = StartingPlayerName;

	// Set the player data names
	PlayerAData.Name = "Player 1";
	PlayerBData.Name = "Player 2";
}

void AFromTheSpotGameModeBase::UpdateMatchData(const FPlayerData& NewPlayerAData,
	const FPlayerData& NewPlayerBData)
{
	// Updates the data, updates the hud
	PlayerAData = NewPlayerAData;
	PlayerBData = NewPlayerBData;
	HUDUpdateMatchData(PlayerAData, PlayerBData);

	UpdateMatchMaterials();
}

void AFromTheSpotGameModeBase::SetAttackInformation(const FVector NewShotLocation, const float NewTimingMultiplier)
{
	// Updates the data
	ShotLocation = NewShotLocation;
	TimingMultiplier = NewTimingMultiplier;

	// Change the state, attack turn is done
	StartNextMatchState();
}

FVector AFromTheSpotGameModeBase::GetShotLocation() const
{
	return ShotLocation;
}

void AFromTheSpotGameModeBase::SetDefendInformation(const FVector NewSaveLocation)
{
	// Updates the data
	SaveLocation = NewSaveLocation;

	// Change the state, defend turn is done
	StartNextMatchState();
}

void AFromTheSpotGameModeBase::BlowWhistle()
{
	// Check the match attacker is valid
	if (!IsValid(MatchAttacker))
	{
		return;
	}

	// Tell the attacker to take the penalty
	MatchAttacker->BP_TakePenalty();
}

void AFromTheSpotGameModeBase::TakePenalty()
{
	// Check the ball is valid
	if (!IsValid(MatchBall))
	{
		return;
	}

	// Check the goal is valid
	if (!IsValid(MatchGoal))
	{
		return;
	}

	// Grab the world, check the world is valid
	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	// Grab the dive info based on the cached save location
	const FDivePointInfo DivePointInfo = MatchGoal->GetDiveInfo(SaveLocation);

	// Tell the goalkeeper to dive
	MatchGoalkeeper->BP_Dive(DivePointInfo, TimingMultiplier);

	// Setup the final shot location vector
	FVector FinalShotLocation = ShotLocation;

	// IF the timing multiplier is less than a quarter
	if (TimingMultiplier <= 0.25f)
	{
		// Update the final shot to be a random bad one
		FinalShotLocation = MatchGoal->GetRandomBadShotLocation();
	}

	// Tell the match ball to shoot
	MatchBall->Shoot(FinalShotLocation, TimingMultiplier);

	// Set the penalty missed timer
	World->GetTimerManager().SetTimer(PenaltyMissedTimerHandle, this, &AFromTheSpotGameModeBase::GoalMissed, MaxPenaltyShotTime);
}

void AFromTheSpotGameModeBase::GoalScored()
{
	// Check if the round has been decided
	if (bRoundDecided)
	{
		return;
	}

	// Grab the current match state, check its valid
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	// Check the player match hud is valid
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	// Increase the correct players data
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

	// Invalidate the timer
	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, PenaltyMissedTimerHandle);

	// Update the hud
	PlayerMatchHUD->PenaltyResult(true, AttackingPlayerName);

	// Start the match state timer
	CurrentMatchState->ActivateRoundTimer(true);

	// Set round decided to true
	bRoundDecided = true;
}

void AFromTheSpotGameModeBase::GoalMissed()
{
	// Check if the round has been decided
	if (bRoundDecided)
	{
		return;
	}

	// Grab the current match state, check its valid
	UFromTheSpotMatchStateBase* CurrentMatchState = CurrentMatchStateInfo.ClassReference;
	if (!IsValid(CurrentMatchState))
	{
		return;
	}

	// Check the player match hud is valid
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	// Increase the correct players data
	if (AttackingPlayerName == PlayerAData.Name)
	{
		PlayerAData.PenaltiesTaken++;
	}
	else if (AttackingPlayerName == PlayerBData.Name)
	{
		PlayerBData.PenaltiesTaken++;
	}

	// Invalidate the timer
	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, PenaltyMissedTimerHandle);

	// Update the hud
	PlayerMatchHUD->PenaltyResult(false, AttackingPlayerName);

	// Start the match state timer
	CurrentMatchState->ActivateRoundTimer(true);

	// Set round decided to true
	bRoundDecided = true;
}

void AFromTheSpotGameModeBase::CheckEndMatch()
{
	// Set the default variables 
	bool bEndMatch = false;
	FPlayerData WinningPlayer = FPlayerData();
	const int PlayerAPenaltiesTaken = PlayerAData.PenaltiesTaken;
	const int PlayerBPenaltiesTaken = PlayerBData.PenaltiesTaken;

	// Check if the match should be put into sudden death, if both have taken 5 pens
	if (!bSuddenDeath && PlayerAPenaltiesTaken == 5 && PlayerBPenaltiesTaken == 5)
	{
		bSuddenDeath = true;
	}

	// Set the player scores
	const int PlayerAScore = PlayerAData.Score;
	const int PlayerBScore = PlayerBData.Score;
	
	if (!bSuddenDeath)
	{
		// If player A has a higher score and player B can't take enough penalties to match the score
		if (PlayerAScore > (PlayerBScore + (5 - PlayerBData.PenaltiesTaken)))
		{
			bEndMatch = true;
			WinningPlayer = PlayerAData;
		}
		// If player B has a higher score and player A can't take enough penalties to match the score
		else if (PlayerBScore > (PlayerAScore + (5 - PlayerAData.PenaltiesTaken)))
		{
			bEndMatch = true;
			WinningPlayer = PlayerBData;
		}
	}
	else
	{
		// Both have taken the same amount
		if (PlayerAPenaltiesTaken == PlayerBPenaltiesTaken)
		{
			// If player A has a 1 goal advantage
			if (PlayerAScore > PlayerBScore)
			{
				bEndMatch = true;
				WinningPlayer = PlayerAData;
			}
			// If player B has a 1 goal advantage
			else if (PlayerBScore > PlayerAScore)
			{
				bEndMatch = true;
				WinningPlayer = PlayerBData;
			}
		}
	}
	
	if (bEndMatch)
	{
		// Puts the match into post match
		EndMatch();
	}
	else
	{
		// If its sudden death, the match hasn't ended and both players have taken 5 pens
		if (bSuddenDeath && !bEndMatch && PlayerAPenaltiesTaken % 5 == 0 && PlayerBPenaltiesTaken % 5 == 0)
		{
			// Clear the score images
			HUDClearScoreImages();
		}

		// Flip the player names ready for next round
		FlipPlayerNames();

		// Check the ball is valid
		if (!IsValid(MatchBall))
		{
			return;
		}

		// Reset the ball and bool
		MatchBall->ResetToStart();
		bRoundDecided = false;

		// Set the index to the start so it changes to attack
		CurrentMatchStateIndex = 0;
	}
}

void AFromTheSpotGameModeBase::FlipPlayerNames()
{
	// Swaps the player names to each other
	if (AttackingPlayerName == PlayerAData.Name)
	{
		AttackingPlayerName = PlayerBData.Name;
	}
	else if (AttackingPlayerName == PlayerBData.Name)
	{
		AttackingPlayerName = PlayerAData.Name;
	}

	// Updates the hud
	HUDFlipPlayerNames();

	// Update the materials
	UpdateMatchMaterials();
}

void AFromTheSpotGameModeBase::UpdateMatchMaterials()
{
	// Check the goalkeeper is valid
	if (!IsValid(MatchGoalkeeper))
	{
		return;
	}

	// Check the attacker is valid
	if (!IsValid(MatchAttacker))
	{
		return;
	}

	// Work out who's attacking
	if (AttackingPlayerName == PlayerAData.Name)
	{
		// Player A attacking, player B defending
		MatchAttacker->BP_UpdateMaterial(PlayerAData.TeamType, PlayerAData.BootsType);
		MatchGoalkeeper->BP_UpdateMaterial(PlayerBData.GlovesType);
	}
	else
	{
		// Player B attacking, player A attacking
		MatchAttacker->BP_UpdateMaterial(PlayerBData.TeamType, PlayerBData.BootsType);
		MatchGoalkeeper->BP_UpdateMaterial(PlayerAData.GlovesType);
	}
}

EGameModeType AFromTheSpotGameModeBase::GetGameModeType() const
{
	return GameModeType;
}

void AFromTheSpotGameModeBase::HUDMatchStateStarted(const EMatchState NewMatchState)
{
	// Checks the hud is valid
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->MatchStateStarted(NewMatchState);
}

void AFromTheSpotGameModeBase::HUDCoinFlipDecided(const bool bPlayer1Heads, const bool bPlayer2Heads,
                                                  const ECoinFlipResult CoinFlipResult, const FString& StartingPlayerName)
{
	// Checks the hud is valid
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->CoinFlipDecided(bPlayer1Heads, bPlayer2Heads, CoinFlipResult, StartingPlayerName);
}

void AFromTheSpotGameModeBase::HUDFlipPlayerNames()
{
	// Checks the hud is valid
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->FlipPlayerNames();
}

void AFromTheSpotGameModeBase::HUDUpdateMatchData(const FPlayerData& NewPlayerAData, const FPlayerData& NewPlayerBData)
{
	// Checks the hud is valid
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->UpdateMatchData(NewPlayerAData, NewPlayerBData);
}

void AFromTheSpotGameModeBase::HUDClearScoreImages()
{
	// Checks the hud is valid
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->ClearScoreImages();
}
