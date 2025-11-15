// Confused Minds Inc.


#include "UI/Widgets/Essentials/TimerWidget.h"
#include "Misc/Timespan.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UTimerWidget::NativeConstruct()
{
	SetTime(0, 0, 0);
}

void UTimerWidget::SetTime(float Hours, float Minutes, float Seconds)
{
	Time = FTimespan(Hours, Minutes, Seconds);

	FText FormatPattern;
	FFormatNamedArguments Args;

	FNumberFormattingOptions NumberOptions;
	NumberOptions.SetMinimumIntegralDigits(2);

	if (Time.GetHours() == 0)
	{
		FormatPattern = FText::FromString(TEXT("{Minute}:{Second}"));
		Args.Add(TEXT("Minute"), FText::AsNumber(Time.GetMinutes(), &NumberOptions));
		Args.Add(TEXT("Second"), FText::AsNumber(Time.GetSeconds(), &NumberOptions));
	}
	else
	{
		FormatPattern = FText::FromString(TEXT("{Hour}:{Minute}:{Second}")); 
		Args.Add(TEXT("Hour"), FText::AsNumber(Time.GetHours(), &NumberOptions));
		Args.Add(TEXT("Minute"), FText::AsNumber(Time.GetMinutes(), &NumberOptions));
		Args.Add(TEXT("Second"), FText::AsNumber(Time.GetSeconds(), &NumberOptions));
	}

	FText FormattedText = FText::Format(FormatPattern, Args);
	T_Time->SetText(FormattedText);
}

bool UTimerWidget::IsTimerRunning()
{
	if (TimerHandle.IsValid())
	{
		return GetWorld()->GetTimerManager().IsTimerActive(TimerHandle);
	}

	return false;
}

FText UTimerWidget::ConvertIntToFText(int32 InIntValue)
{
	FString MyString = FString::FromInt(InIntValue);
	FText MyFText = FText::FromString(MyString);
	return MyFText;
}

void UTimerWidget::UpdateEachSecond()
{
	int32 newSecond = bForward ? 1 : -1;
	Time += FTimespan(0, 0, newSecond);
	SetTime(Time.GetHours(), Time.GetMinutes(), Time.GetSeconds());

	if(Time == TimeGoal)
	{
		ClearTimer();
		MainWidgetSwitcher->SetActiveWidgetIndex(1);
		GoalReached.Broadcast();
	}
}

void UTimerWidget::PauseTimer()
{
	if(TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().PauseTimer(TimerHandle);
	}
}

void UTimerWidget::ClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UTimerWidget::SetGoal(float Hours, float Minutes, float Seconds)
{
	TimeGoal = FTimespan(Hours, Minutes, Seconds);
}

void UTimerWidget::StartTimer(bool bIsForward)
{
	bForward = bIsForward;
	MainWidgetSwitcher->SetActiveWidgetIndex(0);

	if(GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTimerWidget::UpdateEachSecond, 1.0f, true);
	}
}
