// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RotateToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UBTT_RotateToPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
