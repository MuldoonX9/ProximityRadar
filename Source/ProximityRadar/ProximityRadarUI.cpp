// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProximityRadarUI.h"

void UProximityRadarUI::UpdateSpeed(float NewSpeed)
{
	// format the speed to KPH or MPH
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);

	// call the Blueprint handler
	OnSpeedUpdate(FormattedSpeed);
}

void UProximityRadarUI::UpdateGear(int32 NewGear)
{
	// call the Blueprint handler
	OnGearUpdate(NewGear);
}

// AlexHoffman addition
void UProximityRadarUI::UpdateHudRadar(const TArray<FVector2D>& carPositions)
{
	// Loop over the number of icons we have
	// If we have more icons than cars, make the remaining icons invisible
	// If we have more cars than icons, don't draw them, the list is sorted by the cars closest to to the player
	for (int i = 0; i < RadarConstants::MaxUiIcons; i++)
	{
		if (i >= carPositions.Num())
		{
			SetPipVisible(i, false);
			continue;
		}
		else 
		{
			FVector2D newSize{ carPositions[i].X, carPositions[i].Y };
			SetPipVisible(i, true);
			OnPipUpdate(i, carPositions[i]);
		}
	}
}

// AlexHoffman addition
void UProximityRadarUI::UpdateRadarBlindspots(EBlindspotLevel typ, bool left)
{
	SetBlindspotArc(typ, left);
}