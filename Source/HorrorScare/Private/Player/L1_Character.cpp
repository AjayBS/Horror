// Confused Minds Inc.


#include "Player/L1_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/BPCFlashlight.h"
#include "Components/BPCInventory.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/BPC_Movement.h"
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

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(FollowCamera);
    CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create first person mesh and attach to camera
    FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FirstPersonMesh->SetupAttachment(FollowCamera);

    // Create gun mesh and attach to first person mesh
    GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(FirstPersonMesh);

    Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
    Flashlight->SetupAttachment(CameraBoom);

    BPCMovementComponent = CreateDefaultSubobject<UBPC_Movement>(TEXT("MovementComponent"));
    BPCInventoryComponent = CreateDefaultSubobject<UBPCInventory>(TEXT("InventoryComponent"));
    BPCFlashlightComponent = CreateDefaultSubobject<UBPCFlashlight>(TEXT("FlashlightComponent"));
    
}

// Called when the game starts or when spawned
void AL1_Character::BeginPlay()
{
	Super::BeginPlay();
    InitializeHUD();
    
    if (BPCMovementComponent)
    {
        BPCMovementComponent->Initialize(this);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MovementComponent is not initialized!"));
    }

    if (BPCFlashlightComponent)
    {
        BPCFlashlightComponent->Initialize(this);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BPCFlashlightComponent is not initialized!"));
    }
}

void AL1_Character::LineTrace(float Length, bool bIsGrabbing)
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
        if (!bIsGrabbing)
        {
            BP_HitActor(HitResult);
        }
        else
        {
            BP_GrabActor(HitResult);
        }
    }
}

void AL1_Character::ToggleFlashlight()
{
    BPCFlashlightComponent->ToggleFlashlight();
}

void AL1_Character::HeadBob()
{
    if ((GetVelocity().Size() >= BPCMovementComponent->WalkSpeed) && !GetCharacterMovement()->IsFalling())
    {
        float Mapped = FMath::GetMappedRangeValueClamped(
            FVector2D(0.0f, GetCharacterMovement()->MaxWalkSpeed),   // Input range
            FVector2D(0.0f, 1.0f),     // Output range
            GetVelocity().Size()
        );

        if ((GetVelocity().Size() >= BPCMovementComponent->SprintSpeed) && !GetCharacterMovement()->IsFalling())
        {
            
            BP_PlayCameraShake(true, Mapped);
        }
        else
        {
            BP_PlayCameraShake(false, Mapped);
        }
    }
}

void AL1_Character::EquipNextWeapon()
{
    uint8 Next = static_cast<uint8>(CurrentWeapon) + 1;

    if( Next >= static_cast<uint8>(EWeaponType::MAX))
	{
		Next = 0; // Loop back to the first weapon
	}

    CurrentWeapon = static_cast<EWeaponType>(Next);
    BP_WeaponChanged();
}

void AL1_Character::EquipPreviousWeapon()
{
    int32 Previous = static_cast<int32>(CurrentWeapon) - 1;

    if (Previous < 0)
    {
        Previous = static_cast<int32>(EWeaponType::MAX) - 1;  // Wrap to last valid value
    }

    CurrentWeapon = static_cast<EWeaponType>(Previous);
    BP_WeaponChanged();
}

void AL1_Character::InitializeHUD()
{
    HUDWidget = CreateWidget<UHGUserWidget>(GetWorld(), HUDWidgetClass);
    if(HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
