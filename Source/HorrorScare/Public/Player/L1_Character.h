// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "L1_Character.generated.h"

class UCameraComponent;

UCLASS()
class HORRORSCARE_API AL1_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AL1_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	UFUNCTION(BlueprintCallable)
	void LineTrace(float Length);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HitActor(FHitResult HitResult);
};
