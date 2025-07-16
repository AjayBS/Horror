// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "InventoryDropdownWidget.generated.h"

class UButton;
class USizeBox;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UInventoryDropdownWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> UseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ExamineButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> DropButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<USizeBox> UseSection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<USizeBox> ExamineSection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<USizeBox> DropSection;
	
};
