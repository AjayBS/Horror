// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "ArrowWidget.generated.h"

class UButton;
class ALockDial;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHorizontalMovementClicked, bool, bIsLeft, int32, RowIndex, int32, ColumnIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FVerticalMovementClicked, bool, bIsBottom, int32, RowIndex, int32, ColumnIndex);

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
	int32 RowIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockDial")
	int32 ColumnIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockDial")
	bool bAddRotation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockDial")
	bool bIsHighlighted = false;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FHorizontalMovementClicked OnHorizontalMovementClicked;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FVerticalMovementClicked OnVerticalMovementClicked;

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(ALockDial* InLockDial, bool bInAddRotation);

protected:
	TObjectPtr<ALockDial> LockDialRef;

	virtual void NativeConstruct() override;	

	UFUNCTION()
	void RotateLockDial();
	
};
