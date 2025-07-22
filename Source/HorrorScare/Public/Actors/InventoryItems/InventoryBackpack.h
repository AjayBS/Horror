// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryBackpack.generated.h"

UCLASS()
class HORRORSCARE_API AInventoryBackpack : public AActor
{
	GENERATED_BODY()
	
public:
	AInventoryBackpack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 AmountOfSlots;
};
