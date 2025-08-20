// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Managers/HGWorldSubsystem.h"
#include "L1_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHGUserWidget;
class USpotLightComponent;
class UBPC_Movement;
class UBPCInventory;
class UBPCFlashlight;
class UWeaponSystemComponent;

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

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
	TObjectPtr<USpotLightComponent> Flashlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHGUserWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UHGUserWidget> HUDWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBPC_Movement> BPCMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBPCInventory> BPCInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBPCFlashlight> BPCFlashlightComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWeaponSystemComponent> BPCWeaponSystemComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Interactables")
	TObjectPtr<UObject> GrabbedObject;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponData> CurrentWeapons;

	UPROPERTY(BlueprintReadOnly)
	int32 EquippedIndex = 0;

	UFUNCTION(BlueprintCallable)
	void LineTrace(float Length, bool bIsGrabbing);

	UFUNCTION(BlueprintCallable)
	void LineTraceForShooting();
	void StopShooting();

	void ReloadWeapon();

	void ToggleFlashlight();

	void HeadBob();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HitActor(FHitResult HitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GrabActor(FHitResult HitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ReleaseActor();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ShortenPlayerCapsule();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_LengthenPlayerCapsule();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_PlayCameraShake(bool bIsSprinting, float MappedValue);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_WeaponChanged();

	void EquipNextWeapon();
	void EquipPreviousWeapon();

private:
	void InitializeHUD();

};
