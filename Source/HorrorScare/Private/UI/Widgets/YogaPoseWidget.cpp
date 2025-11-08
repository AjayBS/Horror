// Confused Minds Inc.


#include "UI/Widgets/YogaPoseWidget.h"
#include "InputCoreTypes.h"
#include "Components/Overlay.h"
#include "UI/Widgets/Essentials/TimerWidget.h"

FReply UYogaPoseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (Emoticons->IsVisible())
    {
        Emoticons->SetVisibility(ESlateVisibility::Collapsed);
        Sequence->SetVisibility(ESlateVisibility::Visible);

        if (InKeyEvent.GetKey() == EKeys::Up || 
            InKeyEvent.GetKey() == EKeys::Down ||
            InKeyEvent.GetKey() == EKeys::Left ||
            InKeyEvent.GetKey() == EKeys::Right)
        {
            Timer->SetGoal(0, 0, 0);
            Timer->SetTime(0, 0, 5);
            Timer->StartTimer(false);

            return FReply::Handled();
        }
    }
    else if(Sequence->IsVisible())
    {

    }

    return FReply::Handled();
}
