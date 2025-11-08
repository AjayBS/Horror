// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"

#include "TimerWidget.generated.h"

class UTextBlock;
class UWidgetSwitcher;
struct FTimespan;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerGoalReached);

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UTimerWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget = true))
	TObjectPtr<UTextBlock> T_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget = true))
	TObjectPtr<UTextBlock> T_GoalText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget = true))
	TObjectPtr<UWidgetSwitcher> MainWidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan TimeGoal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bForward;

	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FOnTimerGoalReached GoalReached;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetTime(float Hours, float Minutes, float Seconds);

	UFUNCTION(BlueprintCallable)
	void SetGoal(float Hours, float Minutes, float Seconds);

	UFUNCTION(BlueprintCallable)
	void StartTimer(bool bIsForward);

private:
	FTimerHandle TimerHandle;

	FText ConvertIntToFText(int32 InIntValue);

	UFUNCTION()
	void UpdateEachSecond();

	void PauseTimer();
	void ClearTimer();
	
};
