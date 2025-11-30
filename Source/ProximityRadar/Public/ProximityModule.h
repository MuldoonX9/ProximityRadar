// AlexHoffman addition
// The Proximity Module is the brains that drive the UI Radar (or minimap) 
// so the player can see the cars nearby and in their blindspots.
// The proximity module takes in a list of cars,
// outputs to the UI a list of the closest cars to the player
// converted from world space to the players local space.
// It also calculates if the car should trigger a yellow or red blindspot arc
#pragma once

#include "RadarTypes.h"

class AProximityRadarPawn;
class UProximityRadarUI;

class ProximityModule
{
public:
	ProximityModule();
	~ProximityModule() {}

	void SetPlayer(TObjectPtr<AProximityRadarPawn> vehiclePawn);
	void SetUI(TObjectPtr<UProximityRadarUI> vehicleUI);

	void OnUpdate(float Delta);

private:
	void CheckBlindspots(const TArray<RadarPipInfo>& radarInfo);

	/** Pointer to the controlled vehicle pawn */
	TObjectPtr<AProximityRadarPawn> m_VehiclePawn;

	/** Pointer to the UI widget */
	TObjectPtr<UProximityRadarUI> m_VehicleUI;

	EBlindspotLevel m_Left = EBlindspotLevel::AllClear;
	EBlindspotLevel m_Right = EBlindspotLevel::AllClear;
	EBlindspotLevel m_PreviousLeft = EBlindspotLevel::VeryClose;
	EBlindspotLevel m_PreviousRight = EBlindspotLevel::VeryClose;
};

