// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Examination/ExaminationActor.h"
#include "NoteExaminationActor.generated.h"

class UTextRenderComponent;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API ANoteExaminationActor : public AExaminationActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTextRenderComponent> NoteText;

	ANoteExaminationActor();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateBackNoteText(ANotes* Note);
};
