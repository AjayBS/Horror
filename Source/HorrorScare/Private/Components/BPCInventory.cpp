// Confused Minds Inc.


#include "Components/BPCInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HG_PlayerController.h"
#include "UI/Widgets/Inventory/HGInventoryGrid.h"
#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"
#include "UI/Widgets/Inventory/InventoryMenuWidget.h"

// Sets default values for this component's properties
UBPCInventory::UBPCInventory()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBPCInventory::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AHG_PlayerController* HGPlayerController = Cast<AHG_PlayerController>(PC);
	if (HGPlayerController)
	{
		InventoryItems.SetNum(HGPlayerController->InventorySlots);
	}	
}

bool UBPCInventory::AddItem(TSubclassOf<AInventoryItem_Master> Item, float Amount)
{
	bool bSuccess = false;
	int32 localIndex = -1;
	CheckForEmptySlot(bSuccess, localIndex);

	if (bSuccess)
	{
		FInventoryItems NewItem;
		NewItem.Item = Item;
		NewItem.Amount = Amount;
		NewItem.bFilled = true;
		InventoryItems[localIndex] = NewItem;
		UpdateInventorySlot(localIndex);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full!"));
		return false;
	}

	return true;
}

FInventoryItems UBPCInventory::GetItemDataAtIndex(int32 Index)
{
	if (Index < InventoryItems.Num())
	{
		return InventoryItems[Index];
	}

	UE_LOG(LogTemp, Warning, TEXT("Index %d is out of bounds for InventoryItems array."), Index);
	return FInventoryItems(); // Return an empty struct if index is out of bounds
}

void UBPCInventory::UpdateInventorySlot(int32 Index)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AHG_PlayerController* HGPlayerController = Cast<AHG_PlayerController>(PC);
	if (HGPlayerController && HGPlayerController->InventoryWidget && HGPlayerController->InventoryWidget->InventoryGrid)
	{
		if (Index >= 0 && Index < HGPlayerController->InventoryWidget->InventoryGrid->InventorySlotWidgets.Num())
		{
			HGPlayerController->InventoryWidget->InventoryGrid->InventorySlotWidgets[Index]->UpdateSlot();
		}
	}
}

void UBPCInventory::CheckForEmptySlot(bool& bSuccess, int32& Index)
{
	bSuccess = false;
	Index = -1;

	for (int32 i = 0; i < InventoryItems.Num(); i++)
	{
		if (!InventoryItems[i].bFilled)
		{
			Index = i;
			bSuccess = true;
			break;
		}
	}
}

