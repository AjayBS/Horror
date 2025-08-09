// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "ArrowWidget.generated.h"

class UButton;
class ALockDial;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UArrowWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> RotateButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockDial")
	bool bAddRotation = true;

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(ALockDial* InLockDial, bool bInAddRotation);

protected:
	TObjectPtr<ALockDial> LockDialRef;

	virtual void NativeConstruct() override;	

	UFUNCTION()
	void RotateLockDial();
	
};
