// Confused Minds Inc.


#include "AI/Enemy/Essentials/SilentMonster/BTTask_RotateToVector.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTTask_RotateToVector::UBTTask_RotateToVector()
{
    NodeName = "Rotate To Vector";

    // Allow this task to tick if we're doing smooth rotation
    bNotifyTick = true;

    // Setup blackboard key filter to only accept vectors
    TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_RotateToVector, TargetLocationKey));
}

EBTNodeResult::Type UBTTask_RotateToVector::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Get the target location from blackboard
    FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetLocationKey.SelectedKeyName);

    // Check if the vector is valid
    if (TargetLocation.IsZero())
    {
        return EBTNodeResult::Failed;
    }

    // Calculate direction to target
    FVector Direction = TargetLocation - ControlledPawn->GetActorLocation();
    Direction.Z = 0.0f; // Keep rotation on horizontal plane only

    if (Direction.IsNearlyZero())
    {
        return EBTNodeResult::Failed;
    }
    
    FRotator TargetRotation = Direction.Rotation();

    if (bInstantRotation)
    {
        // Instant rotation
        ControlledPawn->SetActorRotation(TargetRotation);
        return EBTNodeResult::Succeeded;
    }
    else
    {
        // Smooth rotation - check if already facing target
        FRotator CurrentRotation = ControlledPawn->GetActorRotation();
        float AngleDifference = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentRotation.Yaw, TargetRotation.Yaw));

        if (AngleDifference <= AcceptableAngle)
        {
            // Already facing the target
            return EBTNodeResult::Succeeded;
        }

        // Need to rotate over time - return InProgress and use TickTask
        return EBTNodeResult::InProgress;
    }
}

void UBTTask_RotateToVector::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Get the target location
    FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetLocationKey.SelectedKeyName);

    // Calculate direction
    FVector Direction = TargetLocation - ControlledPawn->GetActorLocation();
    Direction.Z = 0.0f;

    if (Direction.IsNearlyZero())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FRotator TargetRotation = Direction.Rotation();
    FRotator CurrentRotation = ControlledPawn->GetActorRotation();

    // Calculate the angle difference
    float AngleDifference = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentRotation.Yaw, TargetRotation.Yaw));

    // Check if we're close enough
    if (AngleDifference <= AcceptableAngle)
    {
        ControlledPawn->SetActorRotation(TargetRotation);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    // Smoothly rotate towards target
    FRotator NewRotation = FMath::RInterpConstantTo(
        CurrentRotation,
        TargetRotation,
        DeltaSeconds,
        RotationSpeed
    );

    ControlledPawn->SetActorRotation(NewRotation);
}
