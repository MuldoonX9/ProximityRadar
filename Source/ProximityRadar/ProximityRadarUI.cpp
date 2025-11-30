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
void UProximityRadarUI::UpdateHudRadar(const TArray<RadarPipInfo>& carPositions)
{
	// Loop over the number of icons we have
	// If we have more icons than cars, make the remaining icons invisible
	// If we have more cars than icons, don't draw them, the list is sorted by the cars closest to to the player
	for (int i = 0; i < RadarConstants::MaxUiIcons; i++)
	{
		if (i >= carPositions.Num())
		{
			SetPipVisibility(i, false);
			continue;
		}
		else 
		{
			SetPipVisibility(i, carPositions[i].m_Opacity);
			OnPipUpdate(i, carPositions[i].m_CarLocation);
		}
	}
}

// AlexHoffman addition
void UProximityRadarUI::UpdateRadarBlindspots(EBlindspotLevel typ, bool left)
{
	SetBlindspotArc(typ, left);
}