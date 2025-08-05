// Confused Minds Inc.


#include "Components/WeaponSystemComponent.h"
#include "Player/L1_Character.h"

UWeaponSystemComponent::UWeaponSystemComponent()
{

}

void UWeaponSystemComponent::ShootUSP()
{
    USP_CurrentMagAmmo--;
    if(USP_CurrentMagAmmo < 0)
	{
		USP_CurrentMagAmmo = 0;
		UE_LOG(LogTemp, Verbose, TEXT("UWeaponSystemComponent::ShootUSP - No ammo in magazine"));
		return;
	}

    WeaponLineTrace();
    PlayFireMontage();
}

void UWeaponSystemComponent::ShootAk47()
{
    Ak47_CurrentMagAmmo--;
    if (Ak47_CurrentMagAmmo < 0)
    {
        Ak47_CurrentMagAmmo = 0;
        UE_LOG(LogTemp, Verbose, TEXT("UWeaponSystemComponent::ShootAk47 - No ammo in magazine"));
        return;
    }
   
    WeaponLineTrace();
    PlayFireMontage();
}

void UWeaponSystemComponent::AxeAttack()
{
    if (!bAttacking)
    {
        bAttacking = true;
        WeaponLineTrace();
        PlayFireMontage();
    }    
}


// Called when the game starts
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();

    CharacterRef = Cast<AL1_Character>(GetOwner());
    FPSAnimInstance = CharacterRef->FirstPersonMesh->GetAnimInstance();

    if (FPSAnimInstance)
    {
        FPSAnimInstance->OnMontageEnded.AddDynamic(this, &UWeaponSystemComponent::OnMontageEnded);
    }
}

void UWeaponSystemComponent::WeaponLineTrace()
{
    if (!CharacterRef)
    {
        UE_LOG(LogTemp, Warning, TEXT("UWeaponSystemComponent::WeaponLineTrace - CharacterRef is null"));
        return;
    }

    float Range = 0.f;
    switch (CharacterRef->CurrentWeapon)
    {
    case EWeaponType::USP:
        Range = USP_Range;
        break;
    case EWeaponType::Ak47:
        Range = Ak47_Range;
        break;
    case EWeaponType::Axe:
		Range = 300.f; 
		break;
    default:
        break;
    }

    FVector Start;
    FVector End;
    FHitResult HitResult;

    FRotator PlayerRot;
    CharacterRef->GetController()->GetPlayerViewPoint(Start, PlayerRot);
    End = Start + PlayerRot.Vector() * Range;

    // Line trace parameters
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(CharacterRef); // Ignore self

    // Perform the line trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        TraceParams
    );
}

void UWeaponSystemComponent::PlayFireMontage()
{
    UAnimMontage* CharacterFireMontage = nullptr;
    UAnimationAsset* GunFireAnimation = nullptr;
    switch (CharacterRef->CurrentWeapon)
    { 
    case EWeaponType::USP:
		CharacterFireMontage = USPCharacterFireMontage;
		GunFireAnimation = USPGunFireAnimation;
		break;
    case EWeaponType::Ak47:
        CharacterFireMontage = Ak47CharacterFireMontage;
        GunFireAnimation = Ak47GunFireAnimation;
		break;
    case EWeaponType::Axe:
		CharacterFireMontage = AxeCharacterFireMontage;
		break;
    default:
        break;
    }

    if (FPSAnimInstance && CharacterFireMontage && !FPSAnimInstance->Montage_IsPlaying(CharacterFireMontage))
    {
        FPSAnimInstance->Montage_Play(CharacterFireMontage);
    }

    if (CharacterRef->GunMesh && GunFireAnimation)
    {
        CharacterRef->GunMesh->PlayAnimation(GunFireAnimation, false);
    }
}

void UWeaponSystemComponent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    bAttacking = false;
}

