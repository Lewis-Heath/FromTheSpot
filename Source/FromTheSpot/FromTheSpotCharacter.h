// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
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
	
	// Returns CameraBoom subobject
	USpringArmComponent* GetCameraBoom() const;
	
	// Returns FollowCamera subobject
	UCameraComponent* GetFollowCamera() const;

protected:
	//
	void TouchPressed(const FVector& ScreenLocation);

	//
	void TouchReleased(const FVector& ScreenLocation);

	//
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
};

