// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HorrorAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Hearing;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API AHorrorAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BTTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UAISenseConfig_Hearing* HearingConfig;

protected:
	AHorrorAIController();
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};
