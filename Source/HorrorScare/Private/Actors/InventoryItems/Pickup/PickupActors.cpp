// Confused Minds Inc.


#include "Actors/InventoryItems/Pickup/PickupActors.h"

// Sets default values
APickupActors::APickupActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupActors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

