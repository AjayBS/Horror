// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "Managers/HGWorldSubsystem.h"
#include "InventoryMenuWidget.generated.h"

class UHGInventoryGrid;
class UInventoryDropdownWidget;
class UHGInventorySlotWidget;
class UButton;
class UVerticalBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UInventoryMenuWidget : public UHGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHGInventoryGrid> InventoryGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventoryDropdownWidget> InventoryDropDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CloseDropDownMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> ItemInfoBox;

	virtual void NativeConstruct() override;
	void OpenDropDownMenu(UHGInventorySlotWidget* InSlot);
	void ShowItemInfo(FItemData ItemData);
	void HideItemInfo();

	UFUNCTION()
	void CloseDropDownMenu();

	UFUNCTION()
	void FocusOnCloseButton();

private:
	FTimerHandle DropDownTimerHandle;
};
