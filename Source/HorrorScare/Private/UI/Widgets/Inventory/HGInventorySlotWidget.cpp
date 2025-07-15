// Confused Minds Inc.


#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"
#include "Actors/InventoryItem_Master.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/BPCInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Player/L1_Character.h"

void UHGInventorySlotWidget::InitializeSlot()
{
	PlayerRef = Cast<AL1_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UHGInventorySlotWidget::UpdateSlot()
{
	if (PlayerRef)
	{
		FInventoryItems ItemTempData = PlayerRef->BPCInventoryComponent->GetItemDataAtIndex(Index);
		AInventoryItem_Master* Item = ItemTempData.Item->GetDefaultObject<AInventoryItem_Master>();
		if (Item)
		{
			SlotImage->SetBrushFromTexture(Item->ItemData.Icon);
			SlotAmount->SetText(FText::AsNumber(ItemTempData.Amount));
			SlotAmount->SetVisibility(ItemTempData.Amount > 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item is null in UpdateSlot for index %d"), Index);
		}
	}
}
