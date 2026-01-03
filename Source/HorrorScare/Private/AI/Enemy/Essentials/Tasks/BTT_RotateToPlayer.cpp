// Confused Minds Inc.

#include "AI/Enemy/Essentials/Tasks/BTT_RotateToPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTT_RotateToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* AIPawn = AIController->GetPawn();
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector Direction = PlayerCharacter->GetActorLocation() - AIPawn->GetActorLocation();
	Direction.Z = 0.0f; // Keep rotation on horizontal plane only

	// Create rotation from direction
	FRotator NewRotation = Direction.Rotation();

	// Set the rotation
	AIPawn->SetActorRotation(NewRotation);

	return EBTNodeResult::Succeeded;
}
