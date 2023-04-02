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

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	NONE,
	GREY,
	WHITE,
	MERSYSIDE_RED,
	LONDON_BLUE,
	DORTMUND_YELLOW,
	CELTIC_GREEN,
	MIAMI_PINK,
	TIGER_ORANGE,
};

UENUM(BlueprintType)
enum class EBootsType : uint8
{
	NONE,
	GREY,
	WHITE,
	BLUE,
	GREEN,
	RED,
	YELLOW,
};

UENUM(BlueprintType)
enum class EGlovesType : uint8
{
	NONE,
	GREY,
	WHITE,
	BLUE,
	GREEN,
	RED,
	YELLOW,
};

UENUM(BlueprintType)
enum class EBallType : uint8
{
	NONE,
	BLACK,
	WHITE,
	BLUE,
	GREEN,
	PINK,
	RED,
	YELLOW,
};

UENUM(BlueprintType)
enum class EDifficulty : uint8
{
	NONE,
	EASY,
	MEDIUM,
	HARD,
	IMPOSSIBLE,
};

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	NONE,
	COIN_FLIP,
	ATTACK,
};

UENUM(BlueprintType)
enum class ECoinFlipResult : uint8
{
	NONE,
	HEADS,
	TAILS,
};

UENUM(BlueprintType)
enum class ETurnType : uint8
{
	NONE,
	ATTACK,
	DEFEND,
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

USTRUCT(BlueprintType)
struct FTeamData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Badge = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeamType TeamType = ETeamType::NONE;
};

USTRUCT(BlueprintType)
struct FBootsData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBootsType BootsType = EBootsType::NONE;
};

USTRUCT(BlueprintType)
struct FGlovesData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGlovesType GlovesType = EGlovesType::NONE;
};

USTRUCT(BlueprintType)
struct FBallData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBallType BallType = EBallType::NONE;
};

USTRUCT(BlueprintType)
struct FMatchData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FTeamData Player1TeamData = FTeamData();

	UPROPERTY(BlueprintReadWrite)
	FTeamData Player2TeamData = FTeamData();

	UPROPERTY(BlueprintReadWrite)
	EDifficulty Player1Difficulty = EDifficulty::EASY;

	UPROPERTY(BlueprintReadWrite)
	EDifficulty Player2Difficulty = EDifficulty::EASY;

	UPROPERTY(BlueprintReadWrite)
	EBootsType Player1Boots = EBootsType::GREY;

	UPROPERTY(BlueprintReadWrite)
	EBootsType Player2Boots = EBootsType::WHITE;

	UPROPERTY(BlueprintReadWrite)
	EGlovesType Player1Gloves = EGlovesType::GREY;

	UPROPERTY(BlueprintReadWrite)
	EGlovesType Player2Gloves = EGlovesType::WHITE;

	UPROPERTY(BlueprintReadWrite)
	EBallType MatchBall = EBallType::WHITE;
};

class UFromTheSpotMatchStateBase;

USTRUCT(BlueprintType)
struct FMatchStateData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFromTheSpotMatchStateBase* ClassReference = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EMatchState Type = EMatchState::NONE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Time = -1.0f;
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Score = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString TeamName = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTexture2D* TeamBadge = nullptr;
};




