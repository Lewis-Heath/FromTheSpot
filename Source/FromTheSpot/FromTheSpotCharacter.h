// Copyright Epic Games, Inc. All Rights Reserved.

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
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
};

