// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InventoryItem_Master.h"
#include "InventoryItem_Key.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCARE_API AInventoryItem_Key : public AInventoryItem_Master
{
	GENERATED_BODY()
	
public:
	virtual void UseItem() override;

};
