// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToVector.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UBTTask_RotateToVector : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_RotateToVector();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


protected:
    // The blackboard key containing the vector to rotate towards
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector TargetLocationKey;

    // Rotation speed in degrees per second
    UPROPERTY(EditAnywhere, Category = "Rotation", meta = (ClampMin = "0.0"))
    float RotationSpeed = 360.0f;

    // If true, rotate instantly. If false, rotate smoothly over time
    UPROPERTY(EditAnywhere, Category = "Rotation")
    bool bInstantRotation = false;

    // Acceptable angle difference in degrees before considering rotation complete
    UPROPERTY(EditAnywhere, Category = "Rotation", meta = (ClampMin = "0.0", ClampMax = "180.0"))
    float AcceptableAngle = 5.0f;
	
};
