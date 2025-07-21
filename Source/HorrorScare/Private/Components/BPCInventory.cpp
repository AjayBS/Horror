// Confused Minds Inc.


#include "Components/BPCInventory.h"

#include "Actors/InventoryItem_Master.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HG_PlayerController.h"
#include "UI/Widgets/Inventory/HGInventoryGrid.h"
#include "UI/Widgets/Inventory/HGInventorySlotWidget.h"
#include "UI/Widgets/Inventory/ExaminationWidget.h"
#include "UI/Widgets/Inventory/InventoryMenuWidget.h"

void UBPCInventory::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerControllerRef = Cast<AHG_PlayerController>(PC);
	if (PlayerControllerRef)
	{
		InventoryItems.SetNum(PlayerControllerRef->InventorySlots);
		InventoryWidgetRef = PlayerControllerRef->InventoryWidget;

		ExaminationWidget = CreateWidget<UExaminationWidget>(GetWorld(), ExaminationWidgetClass);
		ExaminationWidget->BPCInventoryRef = this;
		PlayerControllerRef->ExaminationWidget = ExaminationWidget;
	}	
}

bool UBPCInventory::AddItem(TSubclassOf<AInventoryItem_Master> Item, float Amount, int32& Remainder)
{
	bool bSuccess = false;
	Remainder = -1;
	TSubclassOf<AInventoryItem_Master> LocalItem = Item;
	float LocalAmount = Amount;

	AInventoryItem_Master* ItemInstance = Item.GetDefaultObject();
	int32 LocalMaxStackAmount = ItemInstance->ItemData.MaxStackAmount;
	int32 LocalIndex = -1;

	if (LocalMaxStackAmount > 1)
	{
		// Stackable items, first check if the slot is available in inventory
		if (CheckForFreeSlot(LocalItem, LocalIndex))
		{
			// If the item already exists in the inventory, check if it can be stacked
			FInventoryItems ItemData = GetItemDataAtIndex(LocalIndex);

			// If the item can be stacked, check if the amount exceeds the max stack amount
			if (ItemData.Amount + LocalAmount > LocalMaxStackAmount)
			{
				// Fill the item with the max stack amount and call AddItem again with the remaining amount
				float ExcessAmount = ItemData.Amount + LocalAmount - LocalMaxStackAmount;
				FInventoryItems NewItem;
				NewItem.Item = LocalItem;
				NewItem.Amount = LocalMaxStackAmount;
				NewItem.bFilled = true;
				InventoryItems[LocalIndex] = NewItem;
				UpdateInventorySlot(LocalIndex);
				AddItem(LocalItem, ExcessAmount, Remainder);
				return true;
			}
			else
			{
				// Simply add if it doesnt
				FInventoryItems NewItem;
				NewItem.Item = LocalItem;
				NewItem.Amount = ItemData.Amount + LocalAmount;
				NewItem.bFilled = true;
				InventoryItems[LocalIndex] = NewItem;
				UpdateInventorySlot(LocalIndex);
				Remainder = 0;
				return true;
			}
		}
		else
		{
			// New item so check for empty slot and add it else return false
			if (CheckForEmptySlot(LocalIndex))
			{
				// If amount is more than the stack amount then  fill it to the max and call AddItem again with the remaining amount
				if (LocalAmount > LocalMaxStackAmount)
				{
					FInventoryItems NewItem;
					NewItem.Item = LocalItem;
					NewItem.Amount = LocalMaxStackAmount;
					NewItem.bFilled = true;
					InventoryItems[LocalIndex] = NewItem;
					UpdateInventorySlot(LocalIndex);
					AddItem(LocalItem, LocalAmount - LocalMaxStackAmount, Remainder);
					return true;
				}
				else
				{
					// Add the item to the empty slot
					FInventoryItems NewItem;
					NewItem.Item = LocalItem;
					NewItem.Amount = LocalAmount;
					NewItem.bFilled = true;
					InventoryItems[LocalIndex] = NewItem;
					UpdateInventorySlot(LocalIndex);
					Remainder = 0;

					return true;
				}
			}
			else
			{
				// No free or empty slots available
				Remainder = LocalAmount;
				return false;
			}
		}
	}
	else
	{
		// Unique item added to the inventory, if Empty slot is found.
		if (CheckForEmptySlot(LocalIndex))
		{
			FInventoryItems NewItem;
			NewItem.Item = Item;
			NewItem.Amount = 1;
			NewItem.bFilled = true;
			InventoryItems[LocalIndex] = NewItem;
			UpdateInventorySlot(LocalIndex);
			LocalAmount--;
			if (LocalAmount > 0)
			{
				AddItem(LocalItem, LocalAmount, Remainder);
				return true;
			}
			else
			{
				Remainder = 0;
				return true;
			}			
		}

		Remainder = LocalAmount;
		return false;
	}	
}

void UBPCInventory::RemoveItem(int32 Index)
{
	FInventoryItems ItemTempData = GetItemDataAtIndex(Index);
	if (ItemTempData.Amount > 1)
	{
		if (Index >= 0 && Index < InventoryItems.Num())
		{
			InventoryItems[Index].bFilled = true;
			InventoryItems[Index].Item = ItemTempData.Item;
			InventoryItems[Index].Amount = ItemTempData.Amount - 1;
			UpdateInventorySlot(Index);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Index %d is out of bounds for InventoryItems array."), Index);
		}
	}
	else
	{
		// Remove the item from the inventory
		if (Index >= 0 && Index < InventoryItems.Num())
		{
			InventoryItems[Index].bFilled = false;
			InventoryItems[Index].Item = nullptr;
			InventoryItems[Index].Amount = 0;
			UpdateInventorySlot(Index);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Index %d is out of bounds for InventoryItems array."), Index);
		}
	}
	
}

void UBPCInventory::UseItem(int32 Index)
{
	FInventoryItems ItemTempData = GetItemDataAtIndex(Index);
	AInventoryItem_Master* Item = ItemTempData.Item->GetDefaultObject<AInventoryItem_Master>();

	if(ItemTempData.Amount > 0)
	{
		if (Item)
		{
			Item->UseItem();
		}

		RemoveItem(Index);
		InventoryWidgetRef->CloseDropDownMenu();
	}	
}

void UBPCInventory::DropItem(int32 Index)
{
	FInventoryItems ItemTempData = GetItemDataAtIndex(Index);
	int32 LocalAmount = ItemTempData.Amount;
	if (LocalAmount > 0)
	{
		for (int32 i = 0; i < LocalAmount; i++)
		{
			RemoveItem(Index);
		}

		InventoryWidgetRef->CloseDropDownMenu();
		SpawnDroppedItem(ItemTempData.Item, LocalAmount);
	}
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

bool UBPCInventory::CheckForFreeSlot(TSubclassOf<AInventoryItem_Master> Item, int32& Index)
{
	AInventoryItem_Master* ItemInstance = Item.GetDefaultObject();
	Index = -1;
	for(int32 i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i].Item == Item && InventoryItems[i].Amount < ItemInstance->ItemData.MaxStackAmount)
		{
			Index = i;
			return true;
		}
	}

	return false;
}

void UBPCInventory::SpawnDroppedItem(TSubclassOf<AInventoryItem_Master> Item, int32 Amount)
{
	AInventoryItem_Master* ItemInstance = Item.GetDefaultObject();

	FVector Start;
	FVector End;
	FHitResult HitResult;

	FRotator PlayerRot;
	PlayerControllerRef->GetPlayerViewPoint(Start, PlayerRot);
	End = Start + PlayerRot.Vector() * 200.f;

	// Line trace parameters
	FCollisionQueryParams TraceParams;

	// Perform the line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		TraceParams
	);

	FVector SpawnLocation;
	FRotator SpawnRotation(0.f, 0.f, 0.f);
	if (bHit)
	{
		SpawnLocation = HitResult.Location;
	}
	else
	{
		SpawnLocation = HitResult.TraceEnd;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	UWorld* World = GetWorld();

	APickupActors* SpawnedActor = World->SpawnActor<APickupActors>(
		ItemInstance->ItemData.PickupActor,
		FTransform(SpawnRotation, SpawnLocation)
	);

	SpawnedActor->Amount = Amount;
	SpawnedActor->BP_SetSimulation();
}

bool UBPCInventory::CheckForEmptySlot(int32& Index)
{
	Index = -1;

	for (int32 i = 0; i < InventoryItems.Num(); i++)
	{
		if (!InventoryItems[i].bFilled)
		{
			Index = i;
			return true;
		}
	}

	return false;
}

void UBPCInventory::CreateExaminationWidget(int32 Index)
{
	ExaminationWidget->UpdateWidget(Index);
	InventoryWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
	PlayerControllerRef->SetIsOpenInventory(false);

	if(!ExaminationWidget->IsInViewport())
	{
		ExaminationWidget = CreateWidget<UExaminationWidget>(GetWorld(), ExaminationWidgetClass);
		ExaminationWidget->AddToViewport(2);
	}
}

