// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "NoteExaminationWidget.generated.h"

class ANotes;
class AHG_PlayerController;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UNoteExaminationWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Note Examination Widget")
	void UpdateWidget(ANotes* Note);

	UFUNCTION()
	void CloseExaminationWidget();

private:
	TObjectPtr<AHG_PlayerController> PlayerControllerRef;
	TObjectPtr<ANotes> CurrentNote;
	void EnableRotationOperations(bool bEnable);
	
};
