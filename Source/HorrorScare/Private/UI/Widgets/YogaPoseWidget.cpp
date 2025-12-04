// Confused Minds Inc.


#include "UI/Widgets/YogaPoseWidget.h"
#include "Components/Overlay.h"
#include "CommonInputSubsystem.h"
#include "HGGameInstance.h"
#include "InputCoreTypes.h"
#include "Managers/HGWorldSubsystem.h"
#include "UI/Widgets/Essentials/TimerWidget.h"

void UYogaPoseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UCommonInputSubsystem* CommonInputSubsystem = ULocalPlayer::GetSubsystem<UCommonInputSubsystem>(GetOwningPlayer()->GetLocalPlayer());
    if (CommonInputSubsystem)
    {
        ECommonInputType CurrentInputType = CommonInputSubsystem->GetCurrentInputType();
        if (CurrentInputType == ECommonInputType::Gamepad)
        {
            // Gamepad is the active input device
            ShuffledKeys.Add(EKeys::Gamepad_DPad_Left);
            ShuffledKeys.Add(EKeys::Gamepad_DPad_Right);
            ShuffledKeys.Add(EKeys::Gamepad_DPad_Down);
            ShuffledKeys.Add(EKeys::Gamepad_DPad_Up);
            ShuffledKeys.Add(EKeys::Gamepad_FaceButton_Left);
            ShuffledKeys.Add(EKeys::Gamepad_FaceButton_Top);
        }
        else if (CurrentInputType == ECommonInputType::MouseAndKeyboard)
        {
            ShuffledKeys.Add(EKeys::Up);
            ShuffledKeys.Add(EKeys::Down);
            ShuffledKeys.Add(EKeys::Left);
            ShuffledKeys.Add(EKeys::Right);
            ShuffledKeys.Add(EKeys::W);
            ShuffledKeys.Add(EKeys::S);
        }
    } 

    CurrentGameInstance = Cast<UHGGameInstance>(GetGameInstance());
    ShuffleKeyArray();
}

void UYogaPoseWidget::ShuffleKeyArray()
{
    int32 LastIndex = ShuffledKeys.Num() - 1;
    for (int32 i = 0; i <= LastIndex; ++i)
    {
        // Pick a random index between the current index and the last index
        int32 Index = FMath::RandRange(i, LastIndex);

        // Swap the current element with the randomly chosen element
        if (i != Index)
        {
            ShuffledKeys.Swap(i, Index);
        }
    }

    BP_ShuffleKeysSet();
}

bool UYogaPoseWidget::CheckPattern()
{
    bool bPatternValid = true;

    if (PressedKeys.Num() != ShuffledKeys.Num())
    {
        return false;
    }

    for (int32 i = 0; i < ShuffledKeys.Num(); i++)
    {
        if (i + 1 > PressedKeys.Num())
        {
            bPatternValid = false;
            break;
        }

        if (ShuffledKeys[i] != PressedKeys[i])
        {
            bPatternValid = false;
            break;
        }
    }

    return bPatternValid;
}

void UYogaPoseWidget::ResetSequenceAndTimer()
{
    ShuffleKeyArray();
    PressedKeys.Empty();
    Timer->SetTime(0, 0, 5);
}

FReply UYogaPoseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Escape)
    {
        BP_BackKeyPressed();
    }

    if (Emoticons->IsVisible())
    {
        SetCurrentEmotion(InKeyEvent);

        // If no emotion key was pressed, nothing to do
        if (!bIsEmotionKeyPressed)
        {
            return FReply::Handled();
        }
        if (CurrentGameInstance)
        {
            if (const bool* bEmotionEnabled = CurrentGameInstance->EmotionStates.Find(CurrentEmotion))
            {
                if (*bEmotionEnabled)
                {
                    Emoticons->SetVisibility(ESlateVisibility::Collapsed);
                    Sequence->SetVisibility(ESlateVisibility::Visible);

                    Timer->SetGoal(0, 0, 0);
                    Timer->SetTime(0, 0, 5);

                    PressedKeys.Empty();

                    return FReply::Handled();
                }
            }    
        }
    }
    else if(Sequence->IsVisible())
    {
        if (!Timer->IsTimerRunning())
        {
            Timer->StartTimer(false);
            BP_TimerStarted();
        }

        PressedKeys.Add(InKeyEvent.GetKey());
    }

    return FReply::Handled();
}

void UYogaPoseWidget::SetCurrentEmotion(const FKeyEvent& InKeyEvent)
{
    if (const bool* bEmotionEnabled = CurrentGameInstance->EmotionStates.Find(EEmotionsData::FirstBeat))
    {
        if (*bEmotionEnabled)
        {
            CurrentEmotion = EEmotionsData::FirstBeat;
            if (InKeyEvent.GetKey() == EKeys::Left)
            {
                bIsEmotionKeyPressed = true;
            }
           
            return;
        }
    }

    if (InKeyEvent.GetKey() == EKeys::Left)
    {
        CurrentEmotion = EEmotionsData::Anger;
        bIsEmotionKeyPressed = true;
    }
    else if (InKeyEvent.GetKey() == EKeys::Right)
    {
        CurrentEmotion = EEmotionsData::Envy;
        bIsEmotionKeyPressed = true;
    }
    else if (InKeyEvent.GetKey() == EKeys::Up)
    {
        CurrentEmotion = EEmotionsData::Pride;
        bIsEmotionKeyPressed = true;
    }
    else if (InKeyEvent.GetKey() == EKeys::Down)
    {
        CurrentEmotion = EEmotionsData::Greed;
        bIsEmotionKeyPressed = true;
    }
}
