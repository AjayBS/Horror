// Confused Minds Inc.


#include "Actors/Props/Notes.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

ANotes::ANotes()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Paper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Paper->SetupAttachment(Root);

	NoteText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	NoteText->SetupAttachment(Paper);
}