// Written by Lewis Heath.

#include "FromTheSpotCharacter.h"

#include "Football.h"
#include "FootballGoal.h"
#include "FromTheSpotBaseHUD.h"
#include "FromTheSpotGameModeBase.h"
#include "Goalkeeper.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/HUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AFromTheSpotCharacter::AFromTheSpotCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AFromTheSpotCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Grabs the goalkeeper from the scene
	TArray<AActor*> FoundGoalkeepers;
	UGameplayStatics::GetAllActorsOfClass(this, AGoalkeeper::StaticClass(), FoundGoalkeepers);

	// Check its valid
	if (!FoundGoalkeepers.IsValidIndex(0))
	{
		return;
	}

	// Set the reference
	MatchGoalkeeper = Cast<AGoalkeeper>(FoundGoalkeepers[0]);
}

void AFromTheSpotCharacter::SetCurrentTurn(const ETurnType NewTurnType)
{
	// Updates the turn type and turn bools
	CurrentTurn = NewTurnType;
	bTurnTaken = false;
	bCorrectStart = false;
}

void AFromTheSpotCharacter::TouchPressed(const FVector& ScreenLocation)
{
	// Set finger down to true
	bFingerDown = true;

	// Check if the turn has already been taken
	if (bTurnTaken)
	{ 
		return;
	}

	// Check the current turn type isn't none
	if (CurrentTurn == ETurnType::NONE)
	{
		return;
	}

	// Grab the player controller, check its valid
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	// Convert the screen position to world position
	FVector WorldLocation = FVector::ZeroVector;
	FVector WorldDirection = FVector::ZeroVector;
	if(!PlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		return;
	}

	// Line trace from the calculated world position forward
	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHitResult = FHitResult();
	UKismetSystemLibrary::LineTraceSingle(this, WorldLocation, WorldLocation + (WorldDirection * 10000.0f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::Type::None, OutHitResult, true);

	// Check the hit actor is valid
	AActor* HitActor = OutHitResult.GetActor();
	if (!IsValid(HitActor))
	{
		return;
	}
	
	switch (CurrentTurn)
	{
		case ETurnType::ATTACK:
		{
			// If attacking, check the player is starting from the ball
			AFootball* Football = Cast<AFootball>(HitActor);
			if (!IsValid(Football))
			{
				return;
			}
			break;
		}
		case ETurnType::DEFEND:
		{
			// If defending, check the player is starting from the goalkeeper 
			AGoalkeeper* Goalkeeper = Cast<AGoalkeeper>(HitActor);
			if (!IsValid(Goalkeeper))
			{
				return;
			}
			break;
		}
	}

	// Set correct start to true
	bCorrectStart = true;

	// Grab the player base hud check its valid
	AHUD* PlayerHUD = PlayerController->GetHUD();
	if (!IsValid(PlayerHUD))
	{
		return;
	}

	// Grab the player match hud check its valid
	AFromTheSpotBaseHUD* PlayerMatchHUD = Cast<AFromTheSpotBaseHUD>(PlayerHUD);
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	// Freeze the timing indicator
	PlayerMatchHUD->FreezeIndicator(true);

	// Set the start and previous position to the impact point
	StartLocation = OutHitResult.ImpactPoint;
	PreviousLocation = OutHitResult.ImpactPoint;
}

void AFromTheSpotCharacter::TouchReleased(const FVector& ScreenLocation)
{
	// Set finger down to false
	bFingerDown = false;

	// Check if the turn has already been taken
	if (bTurnTaken)
	{
		return;
	}

	// Check correct start is true
	if (!bCorrectStart)
	{
		return;
	}

	// Check the current turn type isn't none
	if (CurrentTurn == ETurnType::NONE)
	{
		return;
	}

	// Grab the player controller, check its valid
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	// Convert the screen position to world position
	FVector WorldLocation = FVector::ZeroVector;
	FVector WorldDirection = FVector::ZeroVector;
	if(!PlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		return;
	}

	// Line trace from the calculated world position forward
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MatchGoalkeeper);
	FHitResult OutHitResult = FHitResult();
	UKismetSystemLibrary::LineTraceSingle(this, WorldLocation, WorldLocation + (WorldDirection * 10000.0f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::Type::None, OutHitResult, true);

	// Check the hit actor is valid
	AActor* HitActor = OutHitResult.GetActor();
	if (!IsValid(HitActor))
	{
		return;
	}

	// Grab the player base hud check its valid
	AHUD* PlayerHUD = PlayerController->GetHUD();
	if (!IsValid(PlayerHUD))
	{
		return;
	}

	// Grab the player match hud check its valid
	AFromTheSpotBaseHUD* PlayerMatchHUD = Cast<AFromTheSpotBaseHUD>(PlayerHUD);
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	// Check the hit actor is the goal, check its valid, if its not reset the params and unfreeze the indicator
	AFootballGoal* FootballGoal = Cast<AFootballGoal>(HitActor);
	if (!IsValid(FootballGoal))
	{
		PlayerMatchHUD->FreezeIndicator(false);
		bCorrectStart = false;
		return;
	}

	// Grab the game mode, check its valid
	AFromTheSpotGameModeBase* GameMode = Cast<AFromTheSpotGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(GameMode))
	{
		return;
	}

	// Set the previous location to the current, set turn taken to true
	PreviousLocation = WorldLocation;
	bTurnTaken = true;

	// Set the necessary information 
	switch (CurrentTurn)
	{
		case ETurnType::ATTACK:
		{
			GameMode->SetAttackInformation(OutHitResult.ImpactPoint, PlayerMatchHUD->GetTimingMultiplier());
			break;
		}
		case ETurnType::DEFEND:
		{
			GameMode->SetDefendInformation(OutHitResult.ImpactPoint);
			break;
		}
	}
}

void AFromTheSpotCharacter::TouchMoved(const FVector& ScreenLocation)
{
	// Check if the turn has already been taken
	if (bTurnTaken)
	{
		return;
	}

	// Check that both correct start and finger down are true
	if (!bCorrectStart || !bFingerDown)
	{
		return;
	}

	// Check the current turn type isn't none
	if (CurrentTurn == ETurnType::NONE)
	{
		return;
	}

	// Grab the player controller, check its valid
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	// Convert the screen position to world position
	FVector NewLocation = FVector::ZeroVector;
    FVector WorldDirection = FVector::ZeroVector;
    if(!PlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, NewLocation, WorldDirection))
    {
    	return;
    }

	// Draw a yellow line with the params
	UKismetSystemLibrary::DrawDebugLine(this, PreviousLocation, NewLocation, FColor::Yellow, 1.0f, 0.05f);

	// Update the previous
	PreviousLocation = NewLocation;
}
