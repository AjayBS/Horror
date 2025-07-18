// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "PickupPromptWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UPickupPromptWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> PromptImage;
	
};
