// Confused Minds Inc.


#include "Player/HG_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Player/L1_Character.h"

void AHG_PlayerController::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 1);
	}

	CharacterRef = Cast<AL1_Character>(GetCharacter());
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
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
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
		GetCharacter()->AddControllerPitchInput(-LookAxisVector.Y * LookSensitivity);
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
