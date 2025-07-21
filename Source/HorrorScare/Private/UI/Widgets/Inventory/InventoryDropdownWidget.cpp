// Confused Minds Inc.


#include "UI/Widgets/Inventory/InventoryDropdownWidget.h"

#include "Components/Button.h"
#include "Components/BPCInventory.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player/L1_Character.h"
#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"

void UInventoryDropdownWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = Cast<AL1_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UseButton->OnReleased.AddDynamic(this, &UInventoryDropdownWidget::UseButtonPressed);
	DropButton->OnReleased.AddDynamic(this, &UInventoryDropdownWidget::DropButtonPressed);
	ExamineButton->OnReleased.AddDynamic(this, &UInventoryDropdownWidget::ExamineButtonPressed);
}

void UInventoryDropdownWidget::UpdateMenu(UHGInventorySlotWidget* InSlot)
{
	if (!InSlot || !PlayerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot or player reference in InventoryDropdownWidget"));
		return;
	}

	SlotIndex = InSlot->Index;
	FInventoryItems ItemData = PlayerRef->BPCInventoryComponent->GetItemDataAtIndex(SlotIndex);
	AInventoryItem_Master* ItemInstance = Cast<AInventoryItem_Master>(ItemData.Item->GetDefaultObject());
	if (ItemInstance)
	{
		if (ItemInstance->ItemData.bCanBeUsed)
		{
			UseSection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			UseSection->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (ItemInstance->ItemData.bCanBeExamined)
		{
			ExamineSection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			ExamineSection->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (ItemInstance->ItemData.bCanBeDropped)
		{
			DropSection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			DropSection->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UInventoryDropdownWidget::UseButtonPressed()
{
	if (PlayerRef)
	{
		PlayerRef->BPCInventoryComponent->UseItem(SlotIndex);
	}
}

void UInventoryDropdownWidget::DropButtonPressed()
{
	if (PlayerRef)
	{
		PlayerRef->BPCInventoryComponent->DropItem(SlotIndex);
	}
}

void UInventoryDropdownWidget::ExamineButtonPressed()
{
	if (PlayerRef)
	{
		PlayerRef->BPCInventoryComponent->CreateExaminationWidget(SlotIndex);
	}
}
