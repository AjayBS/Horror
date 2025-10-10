// Confused Minds Inc.


#include "AI/Enemy/Controller/SilentMonster/SilentMonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"

void ASilentMonsterController::HandlePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

    // Check if it's a hearing stimulus
    if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            BlackboardComp->SetValueAsVector(FName("NoiseLocation"), Stimulus.StimulusLocation);
            bool bHasHeardSomething = BlackboardComp->GetValueAsBool(FName("HeardSomething"));

            if (!bHasHeardSomething)
            {
                BlackboardComp->SetValueAsBool(FName("HeardSomething"), true);
                // AI heard something
                UE_LOG(LogTemp, Warning, TEXT("Heard: %s at location %s"),
                    *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
            }
            else
            {
                BlackboardComp->SetValueAsBool(FName("AttackNoise"), true);
            }
        }
        else
        {
            // Lost track of sound
            BlackboardComp->SetValueAsBool(FName("HeardSomething"), false);
            UE_LOG(LogTemp, Warning, TEXT("Lost sound from: %s"), *Actor->GetName());
        }
    }
}