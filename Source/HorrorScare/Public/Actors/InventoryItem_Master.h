// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Managers/HGWorldSubsystem.h"
#include "InventoryItem_Master.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItems
{
    GENERATED_BODY()

public:    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TSubclassOf<AInventoryItem_Master> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bFilled = false;
};


UCLASS()
class HORRORSCARE_API AInventoryItem_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FItemData ItemData;

	// Sets default values for this actor's properties
	AInventoryItem_Master();


};
