// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotDataTypes.h"
#include "GameFramework/Character.h"
#include "FromTheSpotCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS(config=Game)
class AFromTheSpotCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFromTheSpotCharacter();

	//
	UFUNCTION(BlueprintCallable)
	void SetCurrentTurn(const ETurnType NewTurnType);

	//
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MatchStateStarted(const EMatchState NewMatchState);

	//
	UFUNCTION(BlueprintImplementableEvent)
	void TakePenalty();
	
	// Returns CameraBoom subobject
	USpringArmComponent* GetCameraBoom() const;
	
	// Returns FollowCamera subobject
	UCameraComponent* GetFollowCamera() const;

protected:
	//
	UFUNCTION(BlueprintCallable)
	void TouchPressed(const FVector& ScreenLocation);

	//
	UFUNCTION(BlueprintCallable)
	void TouchReleased(const FVector& ScreenLocation);

	//
	UFUNCTION(BlueprintCallable)
	void TouchMoved(const FVector& ScreenLocation);
	
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bFingerDown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCorrectStart = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bTurnTaken = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETurnType CurrentTurn = ETurnType::NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimingMultiplier = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector StartLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector PreviousLocation = FVector::ZeroVector;
};

