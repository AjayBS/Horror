// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InventoryItem_Master.h"
#include "InventoryItem_FlashlightBattery.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCARE_API AInventoryItem_FlashlightBattery : public AInventoryItem_Master
{
	GENERATED_BODY()

public:
	float BatteryAmount = 100.f; // Amount of battery to add when used
	virtual void UseItem() override;
	
};
