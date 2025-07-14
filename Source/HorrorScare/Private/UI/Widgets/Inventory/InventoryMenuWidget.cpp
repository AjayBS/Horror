// Confused Minds Inc.


#include "UI/Widgets/Inventory/InventoryMenuWidget.h"

#include "UI/Widgets/Inventory/HGInventoryGrid.h"
#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"

void UInventoryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InventoryGrid)
	{
		for (int32 i = 0; i < InventoryGrid->InventorySlotWidgets.Num(); i++)
		{
			InventoryGrid->InventorySlotWidgets[i]->InitializeSlot();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryGrid is not set in InventoryMenuWidget"));
	}
}
