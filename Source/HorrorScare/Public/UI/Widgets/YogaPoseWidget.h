// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "YogaPoseWidget.generated.h"

class UOverlay;
class UTimerWidget;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UYogaPoseWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget = true))
	TObjectPtr<UOverlay> Emoticons;

	UPROPERTY(meta = (BindWidget = true))
	TObjectPtr<UOverlay> Sequence;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = true))
	TObjectPtr<UTimerWidget> Timer;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
};
