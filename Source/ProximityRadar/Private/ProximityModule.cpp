#include "ProximityModule.h"

#include "CarActor.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "ProximityRadarPawn.h"
#include "ProximityRadarUI.h"
#include "RadarTypes.h"
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
	//VehicleUI->UpdateGear(VehiclePawn->GetChaosVehicleMovement()->GetCurrentGear());
	TArray<AActor*> carsToFind;
	
	UGameplayStatics::GetAllActorsOfClass(m_VehiclePawn->GetWorld(), ACarActor::StaticClass(), carsToFind);

	FVector playerLoc = m_VehiclePawn->GetActorLocation();

	// Sort the cars by distance to the player, so closest cars are first
	Algo::Sort(carsToFind, [playerLoc](const AActor* LHS, const AActor* RHS)
		{
			return FVector::DistSquared(playerLoc, LHS->GetActorLocation()) < FVector::DistSquared(playerLoc, RHS->GetActorLocation());
		});
	/*carsToFind.Sort([playerLoc](AActor* a, AActor* b) {
		return FVector::DistSquared(playerLoc, a->GetActorLocation()) < FVector::DistSquared(playerLoc, b->GetActorLocation());
		});*/


	FVector playerForwardVector = m_VehiclePawn->GetActorForwardVector();
	float angleRotation = std::atan2(playerForwardVector.Y, playerForwardVector.X);
	float degRotation = (180.0f / M_PI) * angleRotation;
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, FString::Printf(TEXT("%f"), degRotation));
	}
	TArray<FVector2D> carPositions;
	int i = 0;
	for (AActor* carActor : carsToFind)
	{
		FVector playerToCarVec = carActor->GetActorLocation() - playerLoc;
		//FVector playerToCarVec = playerLoc - carActor->GetActorLocation();
		if (GEngine && i == 0)
		{
			float dist = FVector::Dist(playerLoc, carActor->GetActorLocation());
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, FString::Printf(TEXT("%f"), dist)); 
			if (dist < 100)
			{
				m_VehicleUI->UpdateRadarBlindspots(EBlindspotLevel::VeryClose, true);
			}
			else if (dist < 200)
			{
				m_VehicleUI->UpdateRadarBlindspots(EBlindspotLevel::Close, true);
			}
			else
			{
				m_VehicleUI->UpdateRadarBlindspots(EBlindspotLevel::AllClear, true);
			}
		}
		FVector2D newVec{ 0,0 };
		//newVec.Y = (std::cos(angleRotation)* playerToCarVec.X) - (std::sin(angleRotation) * playerToCarVec.Y);
		//newVec.X = (std::sin(angleRotation) * playerToCarVec.X) + (std::cos(angleRotation) * playerToCarVec.Y);
		newVec.X = (std::cos(angleRotation) * playerToCarVec.Y) - (std::sin(angleRotation) * playerToCarVec.X);
		newVec.Y = (std::sin(angleRotation) * playerToCarVec.Y) + (std::cos(angleRotation) * playerToCarVec.X);
		//newVec.X = playerToCarVec.Y;
		//newVec.Y = playerToCarVec.X / 5.f;
		newVec.Y = newVec.Y * -1.f;// / -5.f;
		carPositions.Add(newVec);
		i++;
	}
	m_VehicleUI->UpdateHudRadar(carPositions);
}


