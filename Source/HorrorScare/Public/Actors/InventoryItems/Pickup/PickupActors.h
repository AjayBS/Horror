// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActors.generated.h"

class AInventoryItem_Master;

UCLASS()
class HORRORSCARE_API APickupActors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<AInventoryItem_Master> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float Amount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
