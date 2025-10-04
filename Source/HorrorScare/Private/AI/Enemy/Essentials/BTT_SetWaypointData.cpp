// Confused Minds Inc.


#include "AI/Enemy/Essentials/BTT_SetWaypointData.h"
#include "AIController.h"
#include "AI/Enemy/AIEnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_SetWaypointData::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AAIEnemyBase* EnemyBase = Cast<AAIEnemyBase>(AIController->GetPawn());
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(WaypointKey.SelectedKeyName, EnemyBase->SetNewWaypointData());

	return EBTNodeResult::Succeeded;
}
