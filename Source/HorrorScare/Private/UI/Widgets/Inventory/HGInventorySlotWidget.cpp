// Confused Minds Inc.


#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"

#include "Actors/InventoryItem_Master.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/BPCInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Player/L1_Character.h"
#include "UI/Widgets/Inventory/InventoryMenuWidget.h"

void UHGInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnReleased.AddDynamic(this, &UHGInventorySlotWidget::OnSlotClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SlotButton is not set in HGInventorySlotWidget"));
	}
}

void UHGInventorySlotWidget::InitializeSlot(UInventoryMenuWidget* InventoryMenu)
{
	PlayerRef = Cast<AL1_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	InventoryMenuRef = InventoryMenu;
	UpdateSlot();
}

void UHGInventorySlotWidget::UpdateSlot()
{
	if (PlayerRef)
	{
		FInventoryItems ItemTempData = PlayerRef->BPCInventoryComponent->GetItemDataAtIndex(Index);
		if(ItemTempData.Item == nullptr)
		{
			SlotButton->SetIsEnabled(false);
			SlotImage->SetBrushFromTexture(EmptyIcon);
			SlotAmount->SetVisibility(ESlateVisibility::Collapsed);
			return;
		}

		AInventoryItem_Master* Item = ItemTempData.Item->GetDefaultObject<AInventoryItem_Master>();
		if (Item)
		{
			SlotButton->SetIsEnabled(true);
			SlotImage->SetBrushFromTexture(Item->ItemData.Icon);
			SlotAmount->SetText(FText::AsNumber(ItemTempData.Amount));
			SlotAmount->SetVisibility(ItemTempData.Amount > 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		}
	}
}

void UHGInventorySlotWidget::OnSlotClicked()
{
	if (InventoryMenuRef)
	{
		InventoryMenuRef->OpenDropDownMenu(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryMenuRef is not set in HGInventorySlotWidget"));
	}
}
