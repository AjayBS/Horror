// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "InventoryMenuWidget.generated.h"

class UHGInventoryGrid;

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

	virtual void NativeConstruct() override;
};
