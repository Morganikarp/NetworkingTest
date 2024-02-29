// Copyright Epic Games, Inc. All Rights Reserved.

#include "PRAPI_NetworkProjectGameMode.h"
#include "PRAPI_NetworkProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

APRAPI_NetworkProjectGameMode::APRAPI_NetworkProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
