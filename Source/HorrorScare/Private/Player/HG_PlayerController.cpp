// Confused Minds Inc.


#include "Player/HG_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

void AHG_PlayerController::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 1);
	}
}

void AHG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHG_PlayerController::Look);
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
		GetCharacter()->AddControllerYawInput(LookAxisVector.X);
		GetCharacter()->AddControllerPitchInput(-LookAxisVector.Y);
	}
}
