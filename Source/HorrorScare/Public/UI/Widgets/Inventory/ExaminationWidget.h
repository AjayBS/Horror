// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "ExaminationWidget.generated.h"

class UTextBlock;
class UBPCInventory;
class AHG_PlayerController;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UExaminationWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;

	TObjectPtr<UBPCInventory> BPCInventoryRef;

	virtual void NativeConstruct() override;
	void UpdateWidget(int32 Index);

	UFUNCTION()
	void CloseExaminationWidget();
	
private:
	TObjectPtr<AHG_PlayerController> PlayerControllerRef;
};
