// Confused Minds Inc.


#include "Actors/Props/LockDial.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ALockDial::ALockDial()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	LockDialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	LockDialMesh->SetupAttachment(Root);	
}

void ALockDial::FindNumber()
{
	Number = FMath::TruncToInt(FMath::Abs(DialRotation / 36.0f));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			FString::Printf(TEXT("The value is: %d"), Number)
		);
	}
}

void ALockDial::RotateDial(bool bReverse)
{
	if (bCanRotate)
	{
		bCanRotate = false;
		if (bReverse)
		{
			BP_RotateDialBackwards();
		}
		else
		{
			BP_RotateDial();
		}		
	}
}

void ALockDial::BeginPlay()
{
	Super::BeginPlay();
	
	SetRandomNumber();
	/*GetWorld()->GetTimerManager().SetTimer(
		RotateTimerHandle,
		this,
		&ALockDial::RotateDial,
		1.0f,
		true,
		2.0f
	);*/
}

void ALockDial::SetRandomNumber()
{
	int32 RandomNumber = FMath::RandRange(0, 9);
	int32 LocalRotation = RandomNumber * 36;
	LockDialMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, LocalRotation));
	DialRotation = LocalRotation;

	FindNumber();
}

