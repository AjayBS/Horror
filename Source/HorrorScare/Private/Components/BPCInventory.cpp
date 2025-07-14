// Confused Minds Inc.


#include "Components/BPCInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HG_PlayerController.h"

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
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full!"));
		return false;
	}

	return true;
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

