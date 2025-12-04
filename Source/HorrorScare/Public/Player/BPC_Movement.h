// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BPC_Movement.generated.h"

class AL1_Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSCARE_API UBPC_Movement : public UActorComponent
{
	GENERATED_BODY()

public:
	TObjectPtr<AL1_Character> Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float WalkSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float MinStamina = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float StaminaRegenRate = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float StaminaDepleteRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float CrouchSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float CrouchHalfHeight = 44.f;
		
	UFUNCTION(BlueprintCallable)
	void Initialize(AL1_Character* InCharacter);

	void StartSprinting();
	void StopSprint();

	void StartCrouch();
	void EndCrouch();

	UFUNCTION()
	void SprintTimer();

	UFUNCTION()
	void OnDelayFinished();

	UFUNCTION()
	void RegenerateStamina();

	UFUNCTION(BlueprintCallable)
	bool IsCrouching() const { return bIsCrouching; }

private:
	float CurrentStamina = 100.f;
	bool bIsCrouching = false;
	FTimerHandle SprintTimerHandle;
	FTimerHandle DelayHandle;
	FTimerHandle StaminaRegenHandle;
		
};
