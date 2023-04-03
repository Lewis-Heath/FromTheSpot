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

void AFromTheSpotCharacter::SetCurrentTurn(const ETurnType NewTurnType)
{
	CurrentTurn = NewTurnType;
	bTurnTaken = false;
	bCorrectStart = false;
}

USpringArmComponent* AFromTheSpotCharacter::GetCameraBoom() const
{
	return CameraBoom;
}

UCameraComponent* AFromTheSpotCharacter::GetFollowCamera() const
{
	return FollowCamera;
}

void AFromTheSpotCharacter::TouchPressed(const FVector& ScreenLocation)
{
	bFingerDown = true;

	if (bTurnTaken)
	{ 
		return;
	}

	if (CurrentTurn == ETurnType::NONE)
	{
		return;
	}
	
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	FVector WorldLocation = FVector::ZeroVector;
	FVector WorldDirection = FVector::ZeroVector;

	if(!PlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		return;
	}

	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHitResult = FHitResult();

	UKismetSystemLibrary::LineTraceSingle(this, WorldLocation, WorldLocation + (WorldDirection * 10000.0f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::Type::None, OutHitResult, true);

	AActor* HitActor = OutHitResult.GetActor();
	if (!IsValid(HitActor))
	{
		return;
	}
	
	switch (CurrentTurn)
	{
		case ETurnType::ATTACK:
		{
			AFootball* Football = Cast<AFootball>(HitActor);
			if (!IsValid(Football))
			{
				return;
			}
			break;
		}
		case ETurnType::DEFEND:
		{
			AGoalkeeper* Goalkeeper = Cast<AGoalkeeper>(HitActor);
			if (!IsValid(Goalkeeper))
			{
				return;
			}
			break;
		}
	}

	bCorrectStart = true;

	AHUD* PlayerHUD = PlayerController->GetHUD();
	if (!IsValid(PlayerHUD))
	{
		return;
	}

	AFromTheSpotBaseHUD* PlayerMatchHUD = Cast<AFromTheSpotBaseHUD>(PlayerHUD);
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}

	PlayerMatchHUD->FreezeIndicator(true);

	StartLocation = OutHitResult.ImpactPoint;
	PreviousLocation = OutHitResult.ImpactPoint;
}

void AFromTheSpotCharacter::TouchReleased(const FVector& ScreenLocation)
{
	bFingerDown = false;

	if (bTurnTaken)
	{
		return;
	}

	if (!bCorrectStart)
	{
		return;
	}

	if (CurrentTurn == ETurnType::NONE)
	{
		return;
	}

	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	FVector WorldLocation = FVector::ZeroVector;
	FVector WorldDirection = FVector::ZeroVector;

	if(!PlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		return;
	}

	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHitResult = FHitResult();

	UKismetSystemLibrary::LineTraceSingle(this, WorldLocation, WorldLocation + (WorldDirection * 10000.0f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::Type::None, OutHitResult, true);

	AActor* HitActor = OutHitResult.GetActor();
	if (!IsValid(HitActor))
	{
		return;
	}

	AHUD* PlayerHUD = PlayerController->GetHUD();
	if (!IsValid(PlayerHUD))
	{
		return;
	}

	AFromTheSpotBaseHUD* PlayerMatchHUD = Cast<AFromTheSpotBaseHUD>(PlayerHUD);
	if (!IsValid(PlayerMatchHUD))
	{
		return;
	}
	
	AFootballGoal* FootballGoal = Cast<AFootballGoal>(HitActor);
	if (!IsValid(FootballGoal))
	{
		bool bIncorrectFinish = true;
		
		if (CurrentTurn == ETurnType::ATTACK)
		{
			AGoalkeeper* Goalkeeper = Cast<AGoalkeeper>(HitActor);
			if (IsValid(Goalkeeper))
			{
				bIncorrectFinish = false;
			}
		}

		if (bIncorrectFinish)
		{
			PlayerMatchHUD->FreezeIndicator(false);
			bCorrectStart = false;
			return;
		}
	}

	AFromTheSpotGameModeBase* GameMode = Cast<AFromTheSpotGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(GameMode))
	{
		return;
	}
	
	PreviousLocation = FVector::ZeroVector;
	bTurnTaken = true;

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
	if (bTurnTaken)
	{
		return;
	}
	
	if (!bCorrectStart || !bFingerDown)
	{
		return;
	}

	if (CurrentTurn == ETurnType::NONE)
	{
		return;
	}

	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
	{
		return;
	}

	FVector NewLocation = FVector::ZeroVector;
    FVector WorldDirection = FVector::ZeroVector;

    if(!PlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, NewLocation, WorldDirection))
    {
    	return;
    }

	UKismetSystemLibrary::DrawDebugLine(this, PreviousLocation, NewLocation, FColor::Yellow, 1.0f, 0.05f);

	PreviousLocation = NewLocation;
}
