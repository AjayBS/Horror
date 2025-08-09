// Confused Minds Inc.


#include "Actors/Props/Lock.h"
#include "Actors/Props/LockDial.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ALock::ALock()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	LockMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	LockMesh->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Root);
}

bool ALock::CheckCode()
{
	bool bLocalSuccess = false;
	for (int32 i = 0; i < LockDials.Num(); i++)
	{
		if (i < LockCombination.Num())
		{
			bLocalSuccess = LockDials[i]->Number == LockCombination[i];
			if (!bLocalSuccess)
			{
				break;
			}
		}
	}
	return bLocalSuccess;
}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;  // Optional: sets who "owns" the actor
	SpawnParams.Instigator = GetInstigator(); // Optional
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < 4; i++)
	{
		FVector SpawnLocation = FVector(0.f, 0.f, 100.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		ALockDial* Dial = GetWorld()->SpawnActor<ALockDial>(LockDialClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams);

		Dial->Index = i; // Set the index for the dial
		Dial->LockRef = this; // Set the reference to the lock

		LockDials.Add(Dial);

		if (i < SocketNames.Num())
		{
			FAttachmentTransformRules Rules(
				EAttachmentRule::SnapToTarget,   // Location
				EAttachmentRule::KeepWorld,   // Rotation
				EAttachmentRule::KeepWorld,      // Scale
				true                             // Weld simulated bodies
			);

			Dial->AttachToComponent(LockMesh, Rules, SocketNames[i]);
		}		
	}	
}

