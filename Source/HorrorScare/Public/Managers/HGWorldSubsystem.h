// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Actors/InventoryItems/Pickup/PickupActors.h"
#include "HGWorldSubsystem.generated.h"

class APickupActors;

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FName ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 MaxStackAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    bool bCanBeUsed = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    bool bCanBeDropped = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TSubclassOf<APickupActors> PickupActor;
};

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UHGWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
};
