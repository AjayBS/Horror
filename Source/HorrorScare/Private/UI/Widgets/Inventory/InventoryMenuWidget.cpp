// Confused Minds Inc.


#include "UI/Widgets/Inventory/InventoryMenuWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/UniformGridSlot.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
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
	int32 Row = GridSlot->GetRow() + 1;
	int32 Column = GridSlot->GetColumn() + 0;

	int32 XSize = InSlot->GetDesiredSize().X + InventoryGrid->InventoryGridPanel->GetSlotPadding().Left + InventoryGrid->InventoryGridPanel->GetSlotPadding().Right;
	int32 YSize = InSlot->GetDesiredSize().Y + InventoryGrid->InventoryGridPanel->GetSlotPadding().Top + InventoryGrid->InventoryGridPanel->GetSlotPadding().Bottom;

	InventoryDropDown->SetRenderTranslation(FVector2D((Column * XSize) + 10.0f, (Row * YSize) + -10.0f));
	InventoryDropDown->UpdateMenu(InSlot);

	InventoryDropDown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CloseDropDownMenuButton->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(
		DropDownTimerHandle,
		this,
		&UInventoryMenuWidget::FocusOnCloseButton,
		0.5f,
		true
	);
}

void UInventoryMenuWidget::ShowItemInfo(FItemData ItemData)
{
	ItemName->SetText(ItemData.ItemName);
	Description->SetText(ItemData.Description);

	ItemInfoBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UInventoryMenuWidget::HideItemInfo()
{
	ItemInfoBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryMenuWidget::CloseDropDownMenu()
{
	InventoryDropDown->SetVisibility(ESlateVisibility::Collapsed);
	CloseDropDownMenuButton->SetVisibility(ESlateVisibility::Collapsed);

	GetWorld()->GetTimerManager().ClearTimer(DropDownTimerHandle);
}

void UInventoryMenuWidget::FocusOnCloseButton()
{
	if (CloseDropDownMenuButton)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		CloseDropDownMenuButton->SetUserFocus(PC);
	}
}
