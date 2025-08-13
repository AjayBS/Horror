// Confused Minds Inc.


#include "UI/Widgets/NoteExaminationWidget.h"

#include "Actors/Examination/NoteExaminationActor.h"
#include "Actors/Props/Notes.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/HGWorldSubsystem.h"
#include "Player/HG_PlayerController.h"

void UNoteExaminationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerControllerRef = Cast<AHG_PlayerController>(PC);
	if (PlayerControllerRef)
	{
		PlayerControllerRef->OnReturn.AddDynamic(this, &UNoteExaminationWidget::CloseExaminationWidget);
	}
	EnableRotationOperations(true);
}

void UNoteExaminationWidget::UpdateWidget(ANotes* Note)
{
	if (Note != nullptr)
	{
		UHGWorldSubsystem* HGWorldSS = GetWorld()->GetSubsystem<UHGWorldSubsystem>();
		if (HGWorldSS && HGWorldSS->NoteExaminationRef)
		{
			HGWorldSS->NoteExaminationRef->NoteText->SetText(Note->NoteText->Text);
		}
	}
}

void UNoteExaminationWidget::CloseExaminationWidget()
{
	if (IsInViewport())
	{
		EnableRotationOperations(false);
		RemoveFromParent();
	}
}

void UNoteExaminationWidget::EnableRotationOperations(bool bEnable)
{
	if (PlayerControllerRef)
	{
		PlayerControllerRef->OpenExaminationWidget(this, bEnable);		
	}
}
