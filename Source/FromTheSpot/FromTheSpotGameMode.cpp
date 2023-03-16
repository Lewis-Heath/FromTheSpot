// Copyright Epic Games, Inc. All Rights Reserved.

#include "FromTheSpotGameMode.h"
#include "FromTheSpotCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFromTheSpotGameMode::AFromTheSpotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
