// Confused Minds Inc.

#include "UI/Widgets/Inventory/ExaminationWidget.h"

#include "Actors/Examination/ExaminationActor.h"
#include "Components/BPCInventory.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HG_PlayerController.h"
#include "Managers/HGWorldSubsystem.h"

void UExaminationWidget::NativeConstruct()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerControllerRef = Cast<AHG_PlayerController>(PC);
	if (PlayerControllerRef)
	{
		PlayerControllerRef->OnReturn.AddDynamic(this, &UExaminationWidget::CloseExaminationWidget);
	}
}

void UExaminationWidget::UpdateWidget(int32 Index)
{
	if (BPCInventoryRef)
	{
		FInventoryItems ItemInstance = BPCInventoryRef->GetItemDataAtIndex(Index);

		UHGWorldSubsystem* HGWorldSS = GetWorld()->GetSubsystem<UHGWorldSubsystem>();
		if (HGWorldSS && HGWorldSS->ExaminationRef)
		{
			HGWorldSS->ExaminationRef->ItemMesh->SetStaticMesh(ItemInstance.Item.GetDefaultObject()->ItemData.ExaminationMesh);			

			HGWorldSS->ExaminationRef->ItemMesh->SetRelativeLocation(FVector(HGWorldSS->ExaminationRef->ItemMesh->GetRelativeLocation().X + ItemInstance.Item.GetDefaultObject()->ItemData.ExaminationMeshOffset,
				HGWorldSS->ExaminationRef->ItemMesh->GetRelativeLocation().Y, 
				HGWorldSS->ExaminationRef->ItemMesh->GetRelativeLocation().Z));

			HGWorldSS->ExaminationRef->ItemMesh->SetRelativeRotation(ItemInstance.Item.GetDefaultObject()->ItemData.ExaminationMeshRotation);
		}

		ItemName->SetText(ItemInstance.Item.GetDefaultObject()->ItemData.ItemName);
		Description->SetText(ItemInstance.Item.GetDefaultObject()->ItemData.Description);
	}
}

void UExaminationWidget::CloseExaminationWidget()
{
	if (IsInViewport())
	{
		PlayerControllerRef->ToggleInventory();
		RemoveFromParent();
	}	
}
