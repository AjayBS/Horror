// Confused Minds Inc.


#include "Animations/HorrorCharacterAnimInstance.h"
#include "AI/Enemy/AIEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHorrorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AAIEnemyBase>(TryGetPawnOwner());

	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UHorrorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAccelaration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
