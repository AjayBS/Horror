// Confused Minds Inc.


#include "Player/HG_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BPC_Movement.h"
#include "Player/L1_Character.h"
#include "UI/Widgets/Inventory/InventoryMenuWidget.h"
#include "UI/Widgets/Inventory/ExaminationWidget.h"

void AHG_PlayerController::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 1);
	}

	CharacterRef = Cast<AL1_Character>(GetCharacter());

	InventoryWidget = CreateWidget<UInventoryMenuWidget>(GetWorld(), InventoryWidgetClass);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	InventoryWidget->AddToViewport();
}

void AHG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHG_PlayerController::Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHG_PlayerController::Move);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHG_PlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AHG_PlayerController::StopJumping);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AHG_PlayerController::Interact);
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Started, this, &AHG_PlayerController::GrabAction);
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Completed, this, &AHG_PlayerController::ReleaseAction);

		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Started, this, &AHG_PlayerController::Flashlight);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AHG_PlayerController::StartSprintAction);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHG_PlayerController::StopSprint);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AHG_PlayerController::Crouch);

		EnhancedInputComponent->BindAction(ReturnAction, ETriggerEvent::Started, this, &AHG_PlayerController::Return);

		EnhancedInputComponent->BindAction(EquipWeaponAction, ETriggerEvent::Triggered, this, &AHG_PlayerController::EquipWeapon);
		EnhancedInputComponent->BindAction(EquipWeaponNextAction, ETriggerEvent::Started, this, &AHG_PlayerController::EquipWeaponNext);
		EnhancedInputComponent->BindAction(EquipWeaponPreviousAction, ETriggerEvent::Started, this, &AHG_PlayerController::EquipWeaponPrevious);

		EnhancedInputComponent->BindAction(ShootWeaponAction, ETriggerEvent::Started, this, &AHG_PlayerController::ShootWeapon);
		EnhancedInputComponent->BindAction(ShootWeaponAction, ETriggerEvent::Completed, this, &AHG_PlayerController::StopShootWeapon);

		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AHG_PlayerController::ReloadWeapon);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHG_PlayerController::ToggleInventory()
{
	if(!bCanOpenInventory)
	{
		return; // Prevent opening inventory if it's not allowed
	}

	if (!bIsInventoryOpen)
	{
		bIsInventoryOpen = true;
		CharacterRef->GetCharacterMovement()->DisableMovement();
		SetIgnoreLookInput(true);
		SetShowMouseCursor(true);
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget()); // Focus on the widget
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		if (ExaminationWidget->IsInViewport())
		{
			ExaminationWidget->RemoveFromParent();
		}

		SetInputMode(InputMode);
	}
	else
	{
		bIsInventoryOpen = false;
		CharacterRef->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		ResetIgnoreLookInput();
		SetShowMouseCursor(false);
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
}

void AHG_PlayerController::OpenExaminationWidget(UHGUserWidget* Widget, bool bOpened)
{
	if (bOpened)
	{
		CharacterRef->GetCharacterMovement()->DisableMovement();
		SetIgnoreLookInput(true);
		SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(Widget->TakeWidget()); // Focus on the widget
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		bCanOpenInventory = false; // Disable inventory opening while examination is open
	}
	else
	{
		CharacterRef->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		ResetIgnoreLookInput();
		SetShowMouseCursor(false);

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bCanOpenInventory = true;
	}
}

void AHG_PlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (GetCharacter() != nullptr)
	{
		// add yaw and pitch input to controller
		GetCharacter()->AddControllerYawInput(LookAxisVector.X * LookSensitivity);
		GetCharacter()->AddControllerPitchInput(LookAxisVector.Y * LookSensitivity);
	}
}

void AHG_PlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (GetCharacter() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
		GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);

		if (CharacterRef)
		{
			CharacterRef->HeadBob();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Character reference is null in Move!"));
		}
	}
}

void AHG_PlayerController::Jump()
{
	GetCharacter()->Jump();
}

void AHG_PlayerController::StopJumping()
{
	GetCharacter()->StopJumping();
}

void AHG_PlayerController::Interact()
{
	CharacterRef->LineTrace(350.0f, false); // Example length, adjust as needed
}

void AHG_PlayerController::Flashlight()
{
	if (CharacterRef)
	{
		CharacterRef->ToggleFlashlight();
	}
}

void AHG_PlayerController::GrabAction()
{
	if (CharacterRef)
	{
		CharacterRef->LineTrace(350.0f, true);
	}	
}

void AHG_PlayerController::ReleaseAction()
{
	if (CharacterRef)
	{
		CharacterRef->BP_ReleaseActor();
	}
}

void AHG_PlayerController::StartSprintAction()
{
	if (CharacterRef)
	{
		CharacterRef->BPCMovementComponent->StartSprinting();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character reference is null in StartSprintAction!"));
	}
}

void AHG_PlayerController::StopSprint()
{
	if (CharacterRef)
	{
		CharacterRef->BPCMovementComponent->StopSprint();
	}
}

void AHG_PlayerController::Crouch()
{
	if (CharacterRef)
	{
		if (CharacterRef->BPCMovementComponent->IsCrouching())
		{
			CharacterRef->BPCMovementComponent->EndCrouch();
		}
		else
		{
			CharacterRef->BPCMovementComponent->StartCrouch();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character reference is null in CrouchAction!"));
	}
}

void AHG_PlayerController::Return()
{
	OnReturn.Broadcast();
}

void AHG_PlayerController::EquipWeapon(const FInputActionValue& Value)
{
	if (CharacterRef)
	{
		float Val = Value.Get<float>();

		if (Val > 0)
		{
			CharacterRef->EquipPreviousWeapon();
		}
		else if (Val < 0)
		{
			CharacterRef->EquipNextWeapon();
		}		
	}
}

void AHG_PlayerController::EquipWeaponPrevious()
{
	if (CharacterRef)
	{
		CharacterRef->EquipPreviousWeapon();
	}
}

void AHG_PlayerController::EquipWeaponNext()
{
	if (CharacterRef)
	{
		CharacterRef->EquipNextWeapon();
	}
}

void AHG_PlayerController::ShootWeapon()
{
	if (CharacterRef)
	{
		CharacterRef->LineTraceForShooting();
	}
}

void AHG_PlayerController::StopShootWeapon()
{
	if (CharacterRef)
	{
		CharacterRef->StopShooting();
	}
}

void AHG_PlayerController::ReloadWeapon()
{
	if (CharacterRef)
	{
		CharacterRef->ReloadWeapon();
	}
}

