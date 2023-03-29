// Written by Lewis Heath.

#pragma once
#include "CoreMinimal.h"
#include "FromTheSpotDataTypes.generated.h"

UENUM(BlueprintType)
enum class EMenuType : uint8
{
	NONE,
	PLAY,
	SHOP,
	SETTINGS,
	TEAM_SELECT,
	PAUSE,
	POST_MATCH,
};

UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	NONE,
	CLASSIC,
	POWERUP,
	PRACTICE,
	TUTORIAL,
};

USTRUCT(BlueprintType)
struct FShopItemData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Badge = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* KitImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor MainColour = FColor::White;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price = 0.99f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bOwned = false;
};


