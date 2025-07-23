// Confused Minds Inc.


#include "Components/BPCFlashlight.h"

#include "Components/SpotLightComponent.h"
#include "Player/L1_Character.h"

UBPCFlashlight::UBPCFlashlight()
{

}

void UBPCFlashlight::ToggleFlashlight()
{
    if (Flashlight->IsVisible())
    {
        Flashlight->SetVisibility(false);
        GetWorld()->GetTimerManager().ClearTimer(FlashlightTimerHandle);
    }
    else if(CurrentBatteryLevel > MinBatteryLevel)
    {
        Flashlight->SetVisibility(true);
        GetWorld()->GetTimerManager().SetTimer(
			FlashlightTimerHandle,
			this,
			&UBPCFlashlight::DepleteBatteryLife,
            DepletionRate, // Deplete every second
			true
		);
    }
}

void UBPCFlashlight::Initialize(AL1_Character* Player)
{
    PlayerRef = Player;
    Flashlight = PlayerRef->Flashlight;
}

void UBPCFlashlight::DepleteBatteryLife()
{
    CurrentBatteryLevel = FMath::Clamp(CurrentBatteryLevel - DepletionAmount, MinBatteryLevel, MaxBatteryLevel);
    if(CurrentBatteryLevel <= MinBatteryLevel)
	{
		Flashlight->SetVisibility(false);
		GetWorld()->GetTimerManager().ClearTimer(FlashlightTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Flashlight battery depleted!"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Current Battery Level: %f"), CurrentBatteryLevel);
	}
}

void UBPCFlashlight::AddBatteryLife(float Amount)
{
   CurrentBatteryLevel = FMath::Clamp(CurrentBatteryLevel + Amount, MinBatteryLevel, MaxBatteryLevel);
}

