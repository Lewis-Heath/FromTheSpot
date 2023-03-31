// Written by Lewis Heath.

#include "FromTheSpotCharacter.h"
#include "Camera/CameraComponent.h"
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
	
	bCorrectStart = false;

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

	
}

void AFromTheSpotCharacter::TouchReleased(const FVector& ScreenLocation)
{
	
}

void AFromTheSpotCharacter::TouchMoved(const FVector& ScreenLocation)
{
	
}
