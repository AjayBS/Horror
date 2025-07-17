// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/InventoryItem_Master.h"
#include "BPCInventory.generated.h"

class UInventoryMenuWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSCARE_API UBPCInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItems> InventoryItems;

	TObjectPtr<UInventoryMenuWidget> InventoryWidgetRef;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(TSubclassOf<AInventoryItem_Master> Item, float Amount, int32& Remainder);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(int32 Index);

	FInventoryItems GetItemDataAtIndex(int32 Index);

	void UpdateInventorySlot(int32 Index);

	bool CheckForFreeSlot(TSubclassOf<AInventoryItem_Master> Item, int32& Remainder);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool CheckForEmptySlot(int32& Index);
};
