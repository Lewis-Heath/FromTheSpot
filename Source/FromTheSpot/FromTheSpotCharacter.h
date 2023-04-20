// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotDataTypes.h"
#include "GameFramework/Character.h"
#include "FromTheSpotCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AGoalkeeper;

UCLASS(config=Game)
class AFromTheSpotCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFromTheSpotCharacter();

	// Sets the current turn type
	UFUNCTION(BlueprintCallable)
	void SetCurrentTurn(const ETurnType NewTurnType);

	// Blueprint event, called when a match state has been initialised
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_MatchStateStarted(const EMatchState NewMatchState);

	// Blueprint event, called when the character should take the penalty
	UFUNCTION(BlueprintImplementableEvent)
	void BP_TakePenalty();

	// Updates the material on the attacker
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_UpdateMaterial(const ETeamType NewTeamType, const EBootsType NewBootsType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// When the user touches the screen
	UFUNCTION(BlueprintCallable)
	void TouchPressed(const FVector& ScreenLocation);

	// When the user releases their finger of the screen
	UFUNCTION(BlueprintCallable)
	void TouchReleased(const FVector& ScreenLocation);

	// When the user moves their finger whilst down on the screen
	UFUNCTION(BlueprintCallable)
	void TouchMoved(const FVector& ScreenLocation);
	
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// Is the users finger down
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bFingerDown = false;

	// Is this the correct start for this turn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCorrectStart = false;

	// Has a correct turn already been taken
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bTurnTaken = false;

	// The current turn type
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETurnType CurrentTurn = ETurnType::NONE;

	// The timing multiplier for the shot
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimingMultiplier = 0.0f;

	// The starting location the user has placed their finger
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector StartLocation = FVector::ZeroVector;

	// The position of the finger on the previous tick
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector PreviousLocation = FVector::ZeroVector;

	// Reference to the goalkeeper actor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AGoalkeeper* MatchGoalkeeper = nullptr;
};

