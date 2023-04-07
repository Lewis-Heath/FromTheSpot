// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Football.generated.h"

UCLASS()
class FROMTHESPOT_API AFootball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFootball();

	// Resets the balls location to the starting location cached and also resets any acting physics
	UFUNCTION(BlueprintCallable)
	void ResetToStart();

	// Shoots the ball based on the target location passed in
	UFUNCTION(BlueprintCallable)
	void Shoot(const FVector& TargetLocation, const float TimingMultiplier);

	// Dampens the velocity of the ball based on the value passed in
	UFUNCTION(BlueprintCallable)
	void DampenVelocity(const float DampenMultiplier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// The mesh for the football
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FootballMesh;

	// The starting location of the football
	FVector StartingLocation = FVector::ZeroVector;
	
	// The power multiplier for the force added to the football when kicked
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PowerMultiplier = 1750.0f;
};
