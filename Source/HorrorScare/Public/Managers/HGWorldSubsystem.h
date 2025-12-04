// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Actors/InventoryItems/Pickup/PickupActors.h"
#include "HGWorldSubsystem.generated.h"

class APickupActors;
class AExaminationActor;
class ANoteExaminationActor;

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

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    EWeaponType Weapon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    bool bIsEquipped = false;
};

UENUM(BlueprintType)
enum class EEmotionsData : uint8
{
    FirstBeat UMETA(DisplayName = "FirstBeat"),
    Anger        UMETA(DisplayName = "Anger"),
    Envy     UMETA(DisplayName = "Envy"),
    Pride        UMETA(DisplayName = "Pride"),
    Greed    UMETA(DisplayName = "Greed")
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<ANoteExaminationActor> NoteExaminationRef;
	
};
