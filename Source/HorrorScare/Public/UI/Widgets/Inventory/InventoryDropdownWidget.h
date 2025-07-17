// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "InventoryDropdownWidget.generated.h"

class UButton;
class USizeBox;
class AL1_Character;
class UHGInventorySlotWidget;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UInventoryDropdownWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> UseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ExamineButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> DropButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<USizeBox> UseSection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<USizeBox> ExamineSection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<USizeBox> DropSection;

	TObjectPtr<AL1_Character> PlayerRef;
	int32 SlotIndex;

	virtual void NativeConstruct() override;
	void UpdateMenu(UHGInventorySlotWidget* InSlot);

	UFUNCTION()
	void UseButtonPressed();
};
