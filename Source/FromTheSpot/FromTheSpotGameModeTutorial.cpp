// Written by Lewis Heath.

#include "FromTheSpotGameModeTutorial.h"

AFromTheSpotGameModeTutorial::AFromTheSpotGameModeTutorial()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the game mode type
	GameModeType = EGameModeType::TUTORIAL;
}
