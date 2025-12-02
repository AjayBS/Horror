// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "YogaPoseWidget.generated.h"

class UOverlay;
class UTimerWidget;
enum class EEmotionsData : uint8;

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEmotionsData CurrentEmotion;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Yoga Pose")
	TArray<FKey> ShuffledKeys;

	TArray<FKey> PressedKeys;

	bool bIsEmotionKeyPressed = false;

	virtual void NativeConstruct() override;
	void ShuffleKeyArray();

	UFUNCTION(BlueprintCallable)
	bool CheckPattern();

	UFUNCTION(BlueprintCallable)
	void ResetSequenceAndTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ShuffleKeysSet();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_TimerStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_BackKeyPressed();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void SetCurrentEmotion(const FKeyEvent& InKeyEvent);
};
