// Confused Minds Inc.


#include "L1GameState.h"

#include "HGGameInstance.h"
#include "Managers/HGWorldSubsystem.h"

bool AL1GameState::IsEmotionsUnlocked()
{
    UHGGameInstance* MainInstance = Cast<UHGGameInstance>(GetWorld()->GetGameInstance());

    if (MainInstance)
    {
        for (const TPair<EEmotionsData, bool>& Pair : MainInstance->EmotionStates)
        {
            if (Pair.Key != EEmotionsData::FirstBeat)
            {
                if (Pair.Value)
                {
                    return true;
                }
            }
        }        
    }

    return false;
}
