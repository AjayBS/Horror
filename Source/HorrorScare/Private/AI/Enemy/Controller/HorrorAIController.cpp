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
	HandlePerceptionUpdated(Actor, Stimulus);
}

void AHorrorAIController::HandlePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}

