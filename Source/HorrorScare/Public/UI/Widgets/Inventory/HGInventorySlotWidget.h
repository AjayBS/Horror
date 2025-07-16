// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "Managers/HGWorldSubsystem.h"
#include "HGInventorySlotWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
class AL1_Character;
class UInventoryMenuWidget;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UHGInventorySlotWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> SlotImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> SlotAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	int32 Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	float Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	TObjectPtr<UTexture2D> EmptyIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	TObjectPtr<UInventoryMenuWidget> InventoryMenuRef;

	TObjectPtr<AL1_Character> PlayerRef;

	virtual void NativeConstruct() override;
	void InitializeSlot(UInventoryMenuWidget* InventoryMenu);
	void UpdateSlot();

	UFUNCTION()
	void OnSlotClicked();

};
