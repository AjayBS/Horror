// Confused Minds Inc.


#include "Player/BPC_Movement.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UBPC_Movement::UBPC_Movement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBPC_Movement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBPC_Movement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBPC_Movement::Initialize(ACharacter* InCharacter)
{
	Character = InCharacter;
	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = WalkSpeed / 2.0f; // Example crouch speed
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is not valid!"));
	}
}

void UBPC_Movement::StartSprinting()
{
	if((CurrentStamina > MinStamina) && (Character->GetVelocity().Size() > 10.f))
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenHandle);

		Character->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		GetWorld()->GetTimerManager().SetTimer(
			SprintTimerHandle,
			this,
			&UBPC_Movement::SprintTimer,
			StaminaDepleteRate,
			true
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough stamina to sprint!"));
	}
}

void UBPC_Movement::StopSprint()
{
	GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);
	Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; // Reset to walk speed

	GetWorld()->GetTimerManager().ClearTimer(DelayHandle);

	GetWorld()->GetTimerManager().SetTimer(
		DelayHandle,
		this,
		&UBPC_Movement::OnDelayFinished,
		5.0f,       // Delay duration in seconds
		false       // Not looping
	);

}

void UBPC_Movement::SprintTimer()
{
	if ((Character->GetVelocity().Size() > 10.f))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,                         
				1.0f,                       
				FColor::Green,              
				FString::Printf(TEXT("Stamina: %.2f"), CurrentStamina)
			);
		}
		CurrentStamina = FMath::Clamp(CurrentStamina - 1.0f, MinStamina, MaxStamina);
		if (CurrentStamina <= MinStamina)
		{
			StopSprint();
		}
		else
		{
			// Optionally, you can update stamina UI or other logic here
		}
	}
	else
	{
		StopSprint(); // Stop sprinting if not moving
	}
	
}

void UBPC_Movement::OnDelayFinished()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(SprintTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(
			StaminaRegenHandle,
			this,
			&UBPC_Movement::RegenerateStamina,
			StaminaRegenRate,
			true
		);
	}
}

void UBPC_Movement::RegenerateStamina()
{
	CurrentStamina = FMath::Clamp(CurrentStamina + 1.0f, MinStamina, MaxStamina);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.0f,
			FColor::Red,
			FString::Printf(TEXT("Stamina: %.2f"), CurrentStamina)
		);
	}
	if (CurrentStamina >= MaxStamina)
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenHandle);
	}
}

