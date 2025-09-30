// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "HorrorBaseAnimInstance.h"
#include "HorrorCharacterAnimInstance.generated.h"

class AAIEnemyBase;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UHorrorCharacterAnimInstance : public UHorrorBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<AAIEnemyBase> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float bHasAccelaration;
};
