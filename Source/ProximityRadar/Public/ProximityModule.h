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
	void CheckBlindspots(const TArray<FVector2D>& carPositions);

	/** Pointer to the controlled vehicle pawn */
	TObjectPtr<AProximityRadarPawn> m_VehiclePawn;

	/** Pointer to the UI widget */
	TObjectPtr<UProximityRadarUI> m_VehicleUI;

	EBlindspotLevel m_Left = EBlindspotLevel::AllClear;
	EBlindspotLevel m_Right = EBlindspotLevel::AllClear;
	EBlindspotLevel m_PreviousLeft = EBlindspotLevel::VeryClose;
	EBlindspotLevel m_PreviousRight = EBlindspotLevel::VeryClose;
};

