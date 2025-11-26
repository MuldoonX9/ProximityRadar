#pragma once
#include "CoreMinimal.h"

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

namespace RadarConstants 
{
	const int MaxDistance = 500;
	const int CloseDistance = 300;
	const int VeryCloseDistance = 200;

	const int VeryCloseXDistance = 400;
	const int CloseXDistance = 700;
	const int VeryCloseYDistance = 260;
	const int CloseYDistance = 300;
	const int CloseYDistanceBelow = 400;
}

