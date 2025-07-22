// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "HGInventoryGrid.generated.h"

class UUniformGridPanel;
class UHGInventorySlotWidget;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UHGInventoryGrid : public UHGUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> InventoryGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UHGInventorySlotWidget> InventorySlotWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UHGInventorySlotWidget*> InventorySlotWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 SlotsPerRow = 4;

	void AddMoreSlots(int32 Amount);

private:
	void CreateInventorySlots(int32 Index);
};
