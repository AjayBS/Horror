// Confused Minds Inc.


#include "AI/Enemy/Controller/HorrorAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"

AHorrorAIController::AHorrorAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
    HearingConfig->HearingRange = 10000.0f; // Adjust as needed
    HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
    HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
    HearingConfig->DetectionByAffiliation.bDetectFriendlies = false; // Or adjust based on requirements

    AIPerceptionComponent->ConfigureSense(*HearingConfig);
}

void AHorrorAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTTree);
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AHorrorAIController::OnTargetPerceptionUpdated);
}

void AHorrorAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    // Check if it's a hearing stimulus
    if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            // AI heard something
            UE_LOG(LogTemp, Warning, TEXT("Heard: %s at location %s"),
                *Actor->GetName(), *Stimulus.StimulusLocation.ToString());

            // React to sound
            // e.g., investigate, alert, attack
        }
        else
        {
            // Lost track of sound
            UE_LOG(LogTemp, Warning, TEXT("Lost sound from: %s"), *Actor->GetName());
        }
    }
}

