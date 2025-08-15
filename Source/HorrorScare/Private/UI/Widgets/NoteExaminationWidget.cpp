// Confused Minds Inc.


#include "UI/Widgets/NoteExaminationWidget.h"

#include "Actors/Examination/NoteExaminationActor.h"
#include "Actors/Props/Notes.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
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
	CurrentNote->SetActorHiddenInGame(true);

	if (CloseButton)
	{
		CloseButton->OnPressed.AddDynamic(this, &UNoteExaminationWidget::CloseButtonClicked);
	}
	
	if (ReadTextButton)
	{
		ReadTextButton->OnPressed.AddDynamic(this, &UNoteExaminationWidget::ReadTextButtonClicked);
	}
}

void UNoteExaminationWidget::UpdateWidget(ANotes* Note)
{
	if (Note != nullptr)
	{
		UHGWorldSubsystem* HGWorldSS = GetWorld()->GetSubsystem<UHGWorldSubsystem>();
		if (HGWorldSS && HGWorldSS->NoteExaminationRef)
		{
			HGWorldSS->NoteExaminationRef->NoteText->SetText(Note->NoteText->Text);
			HGWorldSS->NoteExaminationRef->BP_UpdateBackNoteText(Note);
			CurrentNote = Note;
			NoteText->SetText(Note->WidgetText);
		}
	}
}

void UNoteExaminationWidget::CloseExaminationWidget()
{
	if (IsInViewport())
	{
		EnableRotationOperations(false);
		RemoveFromParent();
		CurrentNote->SetActorHiddenInGame(false);
	}
}

void UNoteExaminationWidget::CloseButtonClicked()
{
	BlackImage->SetVisibility(ESlateVisibility::Collapsed);
	NoteText->SetVisibility(ESlateVisibility::Collapsed);
	CloseButton->SetVisibility(ESlateVisibility::Collapsed);

	NoteImage->SetVisibility(ESlateVisibility::Visible);
}

void UNoteExaminationWidget::ReadTextButtonClicked()
{
	BlackImage->SetVisibility(ESlateVisibility::Visible);
	NoteText->SetVisibility(ESlateVisibility::Visible);
	CloseButton->SetVisibility(ESlateVisibility::Visible);

	NoteImage->SetVisibility(ESlateVisibility::Collapsed);
}

void UNoteExaminationWidget::EnableRotationOperations(bool bEnable)
{
	if (PlayerControllerRef)
	{
		PlayerControllerRef->OpenExaminationWidget(this, bEnable);		
	}
}
