// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HG_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UInventoryMenuWidget;
struct FInputActionValue;
class AL1_Character;
class UExaminationWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReturnAction);

/**
 * 
 */
UCLASS()
class HORRORSCARE_API AHG_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	// Sets default values for this controller's properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LMBAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FlashlightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReturnAction;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnReturnAction OnReturn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryMenuWidget> InventoryWidgetClass;

	TObjectPtr<UInventoryMenuWidget> InventoryWidget;
	TObjectPtr<UExaminationWidget> ExaminationWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float LookSensitivity = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int32 InventorySlots = 8;

	void ToggleInventory();
	void SetIsOpenInventory(bool bIsOpen) { bIsInventoryOpen = bIsOpen; }

protected:
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void Jump();
	void StopJumping();
	void Interact();
	void Flashlight();
	void GrabAction();
	void ReleaseAction();
	void StartSprintAction();
	void StopSprint();

	void Crouch();
	void Return();

private:
	AL1_Character* CharacterRef;	
	bool bIsInventoryOpen = false;
};
