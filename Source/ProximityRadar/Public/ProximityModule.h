#pragma once

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
	int someNumer = 0;

	/** Pointer to the controlled vehicle pawn */
	TObjectPtr<AProximityRadarPawn> m_VehiclePawn;

	/** Pointer to the UI widget */
	TObjectPtr<UProximityRadarUI> m_VehicleUI;
};

