// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BPCFlashlight.generated.h"

class USpotLightComponent;
class AL1_Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSCARE_API UBPCFlashlight : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	TObjectPtr<USpotLightComponent> Flashlight;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery")
	float DepletionAmount = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery")
	float DepletionRate = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battery")
	float CurrentBatteryLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battery")
	float MaxBatteryLevel = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battery")
	float MinBatteryLevel = 50.f;

	// Sets default values for this component's properties
	UBPCFlashlight();
	void ToggleFlashlight();
	void Initialize(AL1_Character* Player);

	UFUNCTION()
	void DepleteBatteryLife();

	void AddBatteryLife(float Amount);
	void SetIntensity();

private:
	TObjectPtr<AL1_Character> PlayerRef;	
	FTimerHandle FlashlightTimerHandle;
		
};
