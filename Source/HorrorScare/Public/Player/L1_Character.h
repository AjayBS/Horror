// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "L1_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHGUserWidget;
class USpotLightComponent;

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
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
	TObjectPtr<USpotLightComponent> SpotLightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHGUserWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UHGUserWidget> HUDWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Interactables")
	TObjectPtr<UObject> GrabbedObject;

	UFUNCTION(BlueprintCallable)
	void LineTrace(float Length, bool bIsGrabbing);

	void ToggleFlashlight();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HitActor(FHitResult HitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GrabActor(FHitResult HitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ReleaseActor();

private:
	void InitializeHUD();
};
