// Confused Minds Inc.


#include "Actors/InventoryItems/InventoryItem_FlashlightBattery.h"

#include "Components/BPCFlashlight.h"
#include "Player/L1_Character.h"

void AInventoryItem_FlashlightBattery::UseItem()
{
	if (PlayerRef && 
		(PlayerRef->BPCFlashlightComponent->CurrentBatteryLevel < PlayerRef->BPCFlashlightComponent->MaxBatteryLevel))
	{
		bUseItemSuccess = true;
		PlayerRef->BPCFlashlightComponent->AddBatteryLife(BatteryAmount);
	}
	else
	{
		bUseItemSuccess = false;
		UE_LOG(LogTemp, Warning, TEXT("AInventoryItem_FlashlightBattery::UseItem()-Flashlight battery is already full or player reference is invalid!"));
	}
}
