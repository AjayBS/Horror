// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "L1GameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorUnlocked, int32, DoorId);

/**
 * 
 */
UCLASS()
class HORRORSCARE_API AL1GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnDoorUnlocked OnDoorUnlocked;
	
};
