// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HG_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

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

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
};
