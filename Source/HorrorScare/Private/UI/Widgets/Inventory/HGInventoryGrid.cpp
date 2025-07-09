// Confused Minds Inc.


#include "UI/Widgets/Inventory/HGInventoryGrid.h"

#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HG_PlayerController.h"
#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"

void UHGInventoryGrid::NativePreConstruct()
{
	Super::NativePreConstruct();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AHG_PlayerController* HGPlayerController = Cast<AHG_PlayerController>(PC);
	if (HGPlayerController)
	{
		for(int32 i = 0; i < HGPlayerController->InventorySlots; ++i)
		{
			UHGInventorySlotWidget* SlotWidget = CreateWidget<UHGInventorySlotWidget>(GetWorld(), InventorySlotWidgetClass);
			if (SlotWidget)
			{
				SlotWidget->Index = i;
				InventorySlotWidgets.Add(SlotWidget);
				InventoryGridPanel->AddChildToUniformGrid(SlotWidget, i / SlotsPerRow, i % SlotsPerRow); 
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("HGInventoryGrid: Failed to create Inventory Slot Widget"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HGInventoryGrid: PlayerController is not of type AHG_PlayerController"));
	}
}
