// AlexHoffman addition

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

	// First, get all the opponent cars
	TArray<AActor*> carsToFind;	
	UGameplayStatics::GetAllActorsOfClass(m_VehiclePawn->GetWorld(), ACarActor::StaticClass(), carsToFind);

	// Sort the cars by distance to the player, so closest cars are first
	FVector playerLoc = m_VehiclePawn->GetActorLocation();
	Algo::Sort(carsToFind, [playerLoc](const AActor* LHS, const AActor* RHS)
		{
			return FVector::DistSquared(playerLoc, LHS->GetActorLocation()) < FVector::DistSquared(playerLoc, RHS->GetActorLocation());
		});

	// Get the rotation of the player car, so we can rotate the opponent cars about it.
	FVector playerForwardVector = m_VehiclePawn->GetActorForwardVector();
	// this is in radians
	float angleRotation = std::atan2(playerForwardVector.Y, playerForwardVector.X);
	
	if (GEngine)
	{
		// For Debug Purposes: show the angle of the opponent car in degrees
		//float degRotation = (180.0f / M_PI) * angleRotation;
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, FString::Printf(TEXT("%f"), degRotation));
	}

	TArray<RadarPipInfo> carPositions;
	for (AActor* carActor : carsToFind)
	{
		// Stop processing if all the cars are too far away
		double distSq = FVector::DistSquared(playerLoc, carActor->GetActorLocation());
		if (distSq > RadarConstants::MaxDistanceSquare)
		{
			break;
		}
		RadarPipInfo newPipInfo;
		// Get a vector from the player to the opponent car
		FVector playerToCarVec = carActor->GetActorLocation() - playerLoc;
		// Using the rotation from above, rotate the vector about the angle
		// This will convert the opponent cars from world space to the player's local space
		newPipInfo.m_CarLocation.X = (std::cos(angleRotation) * playerToCarVec.Y) - (std::sin(angleRotation) * playerToCarVec.X);
		newPipInfo.m_CarLocation.Y = (std::sin(angleRotation) * playerToCarVec.Y) + (std::cos(angleRotation) * playerToCarVec.X);
		// In front in world space is opposite from top in UI space
		newPipInfo.m_CarLocation.Y *= -1.f;

		// This has a gentle fade in for cars near the maximum distance
		// It's much more visually appealing than an icon popping into existence
		if (distSq > RadarConstants::FadeInDistanceSquare)
		{
			// a lerp from Max Distance to Fade in Distance
			float alpha = (RadarConstants::MaxDistanceSquare - distSq)
				/ (RadarConstants::MaxDistanceSquare - RadarConstants::FadeInDistanceSquare);
			newPipInfo.m_Opacity = alpha;
		}
		else
		{
			newPipInfo.m_Opacity = 1.0f;
		}
		carPositions.Add(std::move(newPipInfo));
	}

	// Check to see if any of the cars should trigger the yellow or red blindspot icons.
	CheckBlindspots(carPositions);
	// Finally, pass along the 2D locations of the relevant opponent cars to the UI
	m_VehicleUI->UpdateHudRadar(std::move(carPositions));
}

// This function will take the calculated car positions and show the red or yellow blindspot arcs
// It will also update the UI with the new information
void ProximityModule::CheckBlindspots(const TArray<RadarPipInfo>& radarInfo)
{
	// Favor All clear in the default case
	m_Right = EBlindspotLevel::AllClear;
	m_Left = EBlindspotLevel::AllClear;

	EBlindspotLevel newLevel = EBlindspotLevel::AllClear;
	for (RadarPipInfo carInfo : radarInfo)
	{
		// Check for the closest case fist
		if (abs(carInfo.m_CarLocation.X) < RadarConstants::VeryCloseXDistance
			&& abs(carInfo.m_CarLocation.Y) < RadarConstants::VeryCloseYDistance)
		{
			newLevel = EBlindspotLevel::VeryClose;
		}
		else if (abs(carInfo.m_CarLocation.X) < RadarConstants::CloseXDistance
			&& abs(carInfo.m_CarLocation.Y) < RadarConstants::CloseYDistance)
		{
			newLevel = EBlindspotLevel::Close;
		}
		// This has blindspots show up for cars further to the rear than 
		// they would be if they were in front of the driver.
		// Since they wouldn't be as visible to the driver.
		else if (abs(carInfo.m_CarLocation.X) < RadarConstants::CloseXDistance
			&& carInfo.m_CarLocation.Y > RadarConstants::CloseYDistance
			&& carInfo.m_CarLocation.Y < RadarConstants::CloseYDistanceBelow)
		{
			newLevel = EBlindspotLevel::Close;
		}
		else
		{
			newLevel = EBlindspotLevel::AllClear;
		}

		// Favor the highest level of blindspot (very close)
		if (carInfo.m_CarLocation.X > 0 && newLevel > m_Right)
		{
			m_Right = newLevel;
		}
		else if (carInfo.m_CarLocation.X < 0 && newLevel > m_Left)
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

