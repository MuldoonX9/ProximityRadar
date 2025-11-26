// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProximityRadarWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UProximityRadarWheelRear::UProximityRadarWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}