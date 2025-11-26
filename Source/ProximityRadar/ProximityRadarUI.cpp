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

void UProximityRadarUI::UpdateHudRadar(const TArray<FVector2D>& carPositions)
{
	FVector2D res{ 1,1 };
	GEngine->GameViewport->GetViewportSize(res);
	int halfHorz = 0;// res.Y / 2.f;
	int halfVert = 0;// res.X / 2.f;
	for (int i = 0; i < carPositions.Num(); i++)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, FString::Printf(TEXT("%f, %f"), carPositions[i].X, carPositions[i].Y));
		}
		FVector2D newSize{ carPositions[i].X + halfHorz, carPositions[i].Y + halfVert };
		OnPipUpdate(newSize);

		if (i == 0)
		{
			break;
		}
	}
}

void UProximityRadarUI::UpdateRadarBlindspots(EBlindspotLevel typ, bool left)
{
	SetBlindspotArc(typ, left);
}