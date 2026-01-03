// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_PlayerLooking.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UBTService_PlayerLooking : public UBTService
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector IsSeenKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float NumOfSecondsSeen = 0.0f;
	
};
