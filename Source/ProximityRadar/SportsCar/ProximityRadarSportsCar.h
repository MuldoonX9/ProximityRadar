// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProximityRadarPawn.h"
#include "ProximityRadarSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class AProximityRadarSportsCar : public AProximityRadarPawn
{
	GENERATED_BODY()
	
public:

	AProximityRadarSportsCar();
};
