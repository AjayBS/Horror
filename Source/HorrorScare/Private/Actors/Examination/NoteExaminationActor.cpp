// Confused Minds Inc.


#include "Actors/Examination/NoteExaminationActor.h"

#include "Components/TextRenderComponent.h"

ANoteExaminationActor::ANoteExaminationActor()
{
	NoteText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	NoteText->SetupAttachment(ItemMesh);
}
