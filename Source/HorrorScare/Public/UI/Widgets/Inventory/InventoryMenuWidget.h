// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "InventoryMenuWidget.generated.h"

class UHGInventoryGrid;
class UInventoryDropdownWidget;
class UHGInventorySlotWidget;
class UButton;

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

	virtual void NativeConstruct() override;
	void OpenDropDownMenu(UHGInventorySlotWidget* InSlot);

	UFUNCTION()
	void CloseDropDownMenu();
};
