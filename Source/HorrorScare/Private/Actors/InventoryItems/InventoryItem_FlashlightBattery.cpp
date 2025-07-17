// Confused Minds Inc.


#include "Actors/InventoryItems/InventoryItem_FlashlightBattery.h"

void AInventoryItem_FlashlightBattery::UseItem()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Using flashlight!"));
}
