#pragma once
#include "CoreMinimal.h"

// AlexHoffman addition

UENUM(BlueprintType)
enum class EBlindspotLevel : uint8
{
	/** No cars around */
	AllClear,

	/** A car is close, triggers the yellow blindspot indicator */
	Close,

	/** A car is very close, triggers the red blindspot indicator */
	VeryClose,
};

struct RadarPipInfo
{
	FVector2D m_CarLocation{ 0,0 };
	float m_Opacity{ 1.f };
};

namespace RadarConstants 
{
	// For performance reasons, let's only draw 3 icons
	const int MaxUiIcons = 3;

	// The max distance from the player to process cars for the radar
	constexpr int MaxDistanceSquare = 900 * 900;
	//Start the cars faded out then fade them in
	constexpr int FadeInDistanceSquare = 800 * 800;
	
	// The distance from the player to draw a red blindspot
	const int VeryCloseXDistance = 400;
	const int VeryCloseYDistance = 260;

	// The distance from the player to draw a yellow blindspot
	const int CloseXDistance = 700;	
	const int CloseYDistance = 300;
	// An extra buffer to draw opponent cars that are farther behind the player
	const int CloseYDistanceBelow = 400;
}

