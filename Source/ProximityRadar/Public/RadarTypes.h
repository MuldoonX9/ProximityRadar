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