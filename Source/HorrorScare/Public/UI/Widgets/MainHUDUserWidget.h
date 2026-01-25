// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "MainHUDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UMainHUDUserWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateInteractionProgress(float Percent);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ToggleInteractWidget(bool bShow);
	
};
