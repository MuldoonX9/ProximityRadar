// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RadarTypes.h"
#include "Blueprint/UserWidget.h"
#include "ProximityRadarUI.generated.h"

/**
 *  Simple Vehicle HUD class
 *  Displays the current speed and gear.
 *  Widget setup is handled in a Blueprint subclass.
 */
UCLASS(abstract)
class UProximityRadarUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	/** Controls the display of speed in Km/h or MPH */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle")
	bool bIsMPH = false;

public:

	/** Called to update the speed display */
	void UpdateSpeed(float NewSpeed);

	/** Called to update the gear display */
	void UpdateGear(int32 NewGear);

	/** Called to update the proximity Radar */
	void UpdateHudRadar(const TArray<FVector2D>& carPositions);

	void UpdateRadarBlindspots(EBlindspotLevel typ, bool left);

protected:

	/** Implemented in Blueprint to display the new speed */
	UFUNCTION(BlueprintImplementableEvent, Category="Vehicle")
	void OnSpeedUpdate(float NewSpeed);

	/** Implemented in Blueprint to display the new gear */
	UFUNCTION(BlueprintImplementableEvent, Category="Vehicle")
	void OnGearUpdate(int32 NewGear);

	UFUNCTION(BlueprintImplementableEvent, Category = "Vehicle")
	void OnPipUpdate(FVector2D vec);

	UFUNCTION(BlueprintImplementableEvent, Category = "Vehicle")
	void SetPipVisible(int pipId, bool visible);

	UFUNCTION(BlueprintImplementableEvent, Category = "Vehicle")
	void SetBlindspotArc(EBlindspotLevel blindspotType, bool left);
};
