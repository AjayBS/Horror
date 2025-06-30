// Confused Minds Inc.


#include "Player/L1_Character.h"

#include "Camera/CameraComponent.h"
#include "UI/Widgets/HGUserWidget.h"

// Sets default values
AL1_Character::AL1_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create camera and attach to boom
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(GetMesh(), FName("head"));
    FollowCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AL1_Character::BeginPlay()
{
	Super::BeginPlay();
    InitializeHUD();
}

void AL1_Character::LineTrace(float Length)
{
    FVector Start;
    FVector End;
    FHitResult HitResult;

    FRotator PlayerRot;
    GetController()->GetPlayerViewPoint(Start, PlayerRot);
	End = Start + PlayerRot.Vector() * Length;

    // Line trace parameters
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(this); // Ignore self

    // Perform the line trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        TraceParams
    );

    // Check if we hit something
    if (bHit)
    {
        BP_HitActor(HitResult);
    }
}

void AL1_Character::InitializeHUD()
{
    HUDWidget = CreateWidget<UHGUserWidget>(GetWorld(), HUDWidgetClass);
    if(HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
