// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Notes.generated.h"

class UTextRenderComponent;

UCLASS()
class HORRORSCARE_API ANotes : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Paper;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTextRenderComponent> NoteText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note")
	FText WidgetText;

	ANotes();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

};
