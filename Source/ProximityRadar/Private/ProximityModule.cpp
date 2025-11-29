#include "ProximityModule.h"

#include "CarActor.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "ProximityRadarPawn.h"
#include "ProximityRadarUI.h"
#include <cmath>

#ifndef M_PI
#define M_PI    3.14159265358979323846
#define LOCAL_M_PI 1
#endif

ProximityModule::ProximityModule()
{

}

void ProximityModule::SetPlayer(TObjectPtr<AProximityRadarPawn> vehiclePawn)
{
	m_VehiclePawn = vehiclePawn;
}

void ProximityModule::SetUI(TObjectPtr<UProximityRadarUI> vehicleUI)
{
	m_VehicleUI = vehicleUI;
}

void ProximityModule::OnUpdate(float Delta)
{
	if (UGameplayStatics::IsGamePaused(m_VehiclePawn->GetWorld()))
	{
		return;
	}
	TArray<AActor*> carsToFind;
	
	UGameplayStatics::GetAllActorsOfClass(m_VehiclePawn->GetWorld(), ACarActor::StaticClass(), carsToFind);

	FVector playerLoc = m_VehiclePawn->GetActorLocation();

	// Sort the cars by distance to the player, so closest cars are first
	Algo::Sort(carsToFind, [playerLoc](const AActor* LHS, const AActor* RHS)
		{
			return FVector::DistSquared(playerLoc, LHS->GetActorLocation()) < FVector::DistSquared(playerLoc, RHS->GetActorLocation());
		});

	FVector playerForwardVector = m_VehiclePawn->GetActorForwardVector();
	// this is in radians
	float angleRotation = std::atan2(playerForwardVector.Y, playerForwardVector.X);
	
	if (GEngine)
	{
		// For Debug Purposes: show the angle of the opponent car in degrees
		//float degRotation = (180.0f / M_PI) * angleRotation;
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, FString::Printf(TEXT("%f"), degRotation));
	}
	TArray<FVector2D> carPositions;
	int i = 0;
	for (AActor* carActor : carsToFind)
	{
		FVector playerToCarVec = carActor->GetActorLocation() - playerLoc;
		FVector2D newVec{ 0,0 };
		newVec.X = (std::cos(angleRotation) * playerToCarVec.Y) - (std::sin(angleRotation) * playerToCarVec.X);
		newVec.Y = (std::sin(angleRotation) * playerToCarVec.Y) + (std::cos(angleRotation) * playerToCarVec.X);
		// In front in world space is opposite from top in UI space
		newVec.Y = newVec.Y * -1.f;
		carPositions.Add(newVec);
		i++;
	}
	CheckBlindspots(carPositions);
	m_VehicleUI->UpdateHudRadar(carPositions);
}

// This function will take the calculated car positions and show the red or yellow blindspot arcs
// It will also update the UI with the new information
void ProximityModule::CheckBlindspots(const TArray<FVector2D>& carPositions)
{
	// Favor All clear in the default case
	m_Right = EBlindspotLevel::AllClear;
	m_Left = EBlindspotLevel::AllClear;

	EBlindspotLevel newLevel = EBlindspotLevel::AllClear;
	for (FVector2D carPosition : carPositions)
	{
		// Check for the closest case fist
		if (abs(carPosition.X) < RadarConstants::VeryCloseXDistance
			&& abs(carPosition.Y) < RadarConstants::VeryCloseYDistance)
		{
			newLevel = EBlindspotLevel::VeryClose;
		}
		else if (abs(carPosition.X) < RadarConstants::CloseXDistance
			&& abs(carPosition.Y) < RadarConstants::CloseYDistance)
		{
			newLevel = EBlindspotLevel::Close;
		}
		// This has blindspots show up for cars further to the rear than 
		// they would be if they were in front of the driver.
		// Since they wouldn't be as visible to the driver.
		else if (abs(carPosition.X) < RadarConstants::CloseXDistance
			&& carPosition.Y > RadarConstants::CloseYDistance
			&& carPosition.Y < RadarConstants::CloseYDistanceBelow)
		{
			newLevel = EBlindspotLevel::Close;
		}
		else
		{
			newLevel = EBlindspotLevel::AllClear;
		}

		// Favor the highest level of blindspot (very close)
		if (carPosition.X > 0 && newLevel > m_Right)
		{
			m_Right = newLevel;
		}
		else if (carPosition.X < 0 && newLevel > m_Left)
		{
			m_Left = newLevel;
		}
		newLevel = EBlindspotLevel::AllClear;
	}



	// Only update the blindspots if they have changed since the last update
	// This saves on UI performance
	if (m_PreviousRight != m_Right)
	{
		m_VehicleUI->UpdateRadarBlindspots(m_Right, false);
		m_PreviousRight = m_Right;
		// TODO: (beyond current scope) Send audio event to play spotter audio
	}
	if (m_PreviousLeft != m_Left)
	{
		m_VehicleUI->UpdateRadarBlindspots(m_Left, true);
		m_PreviousLeft = m_Left;
	}
}

