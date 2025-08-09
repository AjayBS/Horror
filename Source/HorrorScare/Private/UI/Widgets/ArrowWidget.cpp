// Confused Minds Inc.

#include "UI/Widgets/ArrowWidget.h"

#include "Actors/Props/LockDial.h"
#include "Components/Button.h"

void UArrowWidget::InitializeWidget(ALockDial* InLockDial, bool bInAddRotation)
{
	if (InLockDial)
	{
		LockDialRef = InLockDial;
		bAddRotation = bInAddRotation;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UArrowWidget::InitializeWidget - LockDialRef is null!"));
	}
}

void UArrowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RotateButton)
	{
		RotateButton->OnClicked.AddDynamic(this, &UArrowWidget::RotateLockDial);
	}
}

void UArrowWidget::RotateLockDial()
{
	LockDialRef->RotateDial(!bAddRotation);
}
