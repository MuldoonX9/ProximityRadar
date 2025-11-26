// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProximityRadarWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UProximityRadarWheelFront::UProximityRadarWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}