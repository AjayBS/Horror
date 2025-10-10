// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemy/Controller/HorrorAIController.h"
#include "SilentMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCARE_API ASilentMonsterController : public AHorrorAIController
{
	GENERATED_BODY()

public:
	void HandlePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
	
};
