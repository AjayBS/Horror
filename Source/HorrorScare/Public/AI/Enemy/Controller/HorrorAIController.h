// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HorrorAIController.generated.h"

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

protected:
	virtual void BeginPlay() override;
	
};
