// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/InventoryItem_Master.h"
#include "BPCInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSCARE_API UBPCInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItems> InventoryItems;

	// Sets default values for this component's properties
	UBPCInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(TSubclassOf<AInventoryItem_Master> Item, float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
	void CheckForEmptySlot(bool& bSuccess, int32& Index);
};
