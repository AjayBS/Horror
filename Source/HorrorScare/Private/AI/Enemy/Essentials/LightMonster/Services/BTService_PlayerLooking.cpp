// Confused Minds Inc.


#include "AI/Enemy/Essentials/LightMonster/Services/BTService_PlayerLooking.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UBTService_PlayerLooking::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) return;

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return;

    // Find the closest player character
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        bool bIsSeen = false;
        FVector PlayerForwardVec = PlayerCharacter->GetMesh()->GetForwardVector();
        FVector Dist = AIPawn->GetActorLocation() - PlayerCharacter->GetActorLocation();
        Dist.Normalize();
        float DotResult = FVector::DotProduct(PlayerForwardVec, Dist);

        if (DotResult > 0.25f && DotResult < 1.0f)
        {
            NumOfSecondsSeen = FMath::Clamp(NumOfSecondsSeen + 0.25f, 0.0f, 1.0f);
            bIsSeen = NumOfSecondsSeen >= 1.0f;
        }
        else
        {
            NumOfSecondsSeen = FMath::Clamp(NumOfSecondsSeen - 0.25f, 0.0f, 1.0f);
        }

        BlackboardComp->SetValueAsBool(IsSeenKey.SelectedKeyName, bIsSeen);
    }
}
