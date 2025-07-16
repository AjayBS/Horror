// Confused Minds Inc.


#include "UI/Widgets/Inventory/InventoryMenuWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/UniformGridSlot.h"
#include "Components/UniformGridPanel.h"
#include "UI/Widgets/Inventory/HGInventoryGrid.h"
#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"
#include "UI/Widgets/Inventory/InventoryDropdownWidget.h"

void UInventoryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InventoryGrid)
	{
		for (int32 i = 0; i < InventoryGrid->InventorySlotWidgets.Num(); i++)
		{
			InventoryGrid->InventorySlotWidgets[i]->InitializeSlot(this);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryGrid is not set in InventoryMenuWidget"));
	}

	if (CloseDropDownMenuButton)
	{
		CloseDropDownMenuButton->OnPressed.AddDynamic(this, &UInventoryMenuWidget::CloseDropDownMenu);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CloseDropDownMenuButton is not set in HGInventorySlotWidget"));
	}
}

void UInventoryMenuWidget::OpenDropDownMenu(UHGInventorySlotWidget* InSlot)
{
	UUniformGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(InSlot);
	int32 Row = GridSlot->Row + 1;
	int32 Column = GridSlot->Column + 0;

	int32 XSize = InSlot->GetDesiredSize().X + InventoryGrid->InventoryGridPanel->SlotPadding.Left + InventoryGrid->InventoryGridPanel->SlotPadding.Right;
	int32 YSize = InSlot->GetDesiredSize().Y + InventoryGrid->InventoryGridPanel->SlotPadding.Top + InventoryGrid->InventoryGridPanel->SlotPadding.Bottom;

	InventoryDropDown->SetRenderTranslation(FVector2D((Column * XSize) + 10.0f, (Row * YSize) + -10.0f));

	InventoryDropDown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CloseDropDownMenuButton->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryMenuWidget::CloseDropDownMenu()
{
	InventoryDropDown->SetVisibility(ESlateVisibility::Collapsed);
	CloseDropDownMenuButton->SetVisibility(ESlateVisibility::Collapsed);
}
