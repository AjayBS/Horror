// Confused Minds Inc.


#include "AI/Enemy/Controller/HorrorAIController.h"

void AHorrorAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTTree);
}
