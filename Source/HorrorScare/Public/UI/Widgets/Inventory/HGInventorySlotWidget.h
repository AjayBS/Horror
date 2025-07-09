// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "HGInventorySlotWidget.generated.h"

class UButton;
class UImage;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true));
	int32 Index;
	
};
