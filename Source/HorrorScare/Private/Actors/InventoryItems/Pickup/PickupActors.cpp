// Confused Minds Inc.


#include "Actors/InventoryItems/Pickup/PickupActors.h"

// Sets default values
APickupActors::APickupActors()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}
