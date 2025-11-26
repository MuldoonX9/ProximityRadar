// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProximityRadarGameMode.h"
#include "ProximityRadarPlayerController.h"

AProximityRadarGameMode::AProximityRadarGameMode()
{
	PlayerControllerClass = AProximityRadarPlayerController::StaticClass();
}
