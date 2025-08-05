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


    AL1_Character* PlayerCharacter = Cast<AL1_Character>(GetOwner());
    if(!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWeaponSystemComponent::ShootUSP - PlayerCharacter is null"));
		return;
	}

    WeaponLineTrace(PlayerCharacter);
    PlayFireMontage(PlayerCharacter);
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

    AL1_Character* PlayerCharacter = Cast<AL1_Character>(GetOwner());
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("UWeaponSystemComponent::ShootUSP - PlayerCharacter is null"));
        return;
    }
   
    WeaponLineTrace(PlayerCharacter);
    PlayFireMontage(PlayerCharacter);
}


// Called when the game starts
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UWeaponSystemComponent::WeaponLineTrace(AL1_Character* CharacterRef)
{
    int32 Range = 0;
    switch (CharacterRef->CurrentWeapon)
    {
    case EWeaponType::USP:
        Range = USP_Range;
        break;
    case EWeaponType::Ak47:
        Range = Ak47_Range;
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

void UWeaponSystemComponent::PlayFireMontage(AL1_Character* CharacterRef)
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
    default:
        break;
    }

    if(!CharacterFireMontage && !GunFireAnimation) return;

    UAnimInstance* FPSAnimInstance = CharacterRef->FirstPersonMesh->GetAnimInstance();
    if (FPSAnimInstance && !FPSAnimInstance->Montage_IsPlaying(CharacterFireMontage))
    {
        FPSAnimInstance->Montage_Play(CharacterFireMontage);
    }

    UAnimInstance* GunAnimInstance = CharacterRef->GunMesh->GetAnimInstance();
    if (CharacterRef->GunMesh)
    {
        CharacterRef->GunMesh->PlayAnimation(GunFireAnimation, false);
    }
}

