// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Actors/InventoryItems/Pickup/PickupActors.h"
#include "HGWorldSubsystem.generated.h"

class APickupActors;
class AExaminationActor;

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 MaxStackAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    bool bCanBeUsed = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    bool bCanBeDropped = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    bool bCanBeExamined = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TSubclassOf<APickupActors> PickupActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TObjectPtr<UStaticMesh> ExaminationMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float ExaminationMeshOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FRotator ExaminationMeshRotation;
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Ak47        UMETA(DisplayName = "Ak47"),
    USP         UMETA(DisplayName = "USP"),
    Axe         UMETA(DisplayName = "Axe"),
    FirstAid    UMETA(DisplayName = "FirstAid"),
    MAX        UMETA(Hidden)
};

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UHGWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AExaminationActor> ExaminationRef;
	
};
