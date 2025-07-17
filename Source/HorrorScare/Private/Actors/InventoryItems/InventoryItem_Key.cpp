// Confused Minds Inc.


#include "Actors/InventoryItems/InventoryItem_Key.h"

void AInventoryItem_Key::UseItem()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Using keys!"));
}
