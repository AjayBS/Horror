// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/HGUserWidget.h"
#include "NoteExaminationWidget.generated.h"

class ANotes;
class AHG_PlayerController;
class UButton;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UNoteExaminationWidget : public UHGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> NoteImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ReadTextButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BlackImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NoteText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Note Examination Widget")
	void UpdateWidget(ANotes* Note);

	UFUNCTION()
	void CloseExaminationWidget();

	UFUNCTION()
	void CloseButtonClicked();

	UFUNCTION()
	void ReadTextButtonClicked();

private:
	TObjectPtr<AHG_PlayerController> PlayerControllerRef;
	TObjectPtr<ANotes> CurrentNote;
	void EnableRotationOperations(bool bEnable);
	
};
