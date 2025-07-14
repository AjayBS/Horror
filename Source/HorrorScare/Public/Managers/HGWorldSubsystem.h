// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HGWorldSubsystem.generated.h"

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
};

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UHGWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
};
