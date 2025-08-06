// Confused Minds Inc.


#include "Components/WeaponSystemComponent.h"
#include "Player/L1_Character.h"

UWeaponSystemComponent::UWeaponSystemComponent()
{

}

void UWeaponSystemComponent::ShootWeapon()
{
    switch (CharacterRef->CurrentWeapon)
    {
    case EWeaponType::Ak47:
        ShootAk47();

        GetWorld()->GetTimerManager().SetTimer(
            Ak47TimerHandle,
            this,
            &UWeaponSystemComponent::ShootAk47,
            GetAk47ShootRate(),
            true
        );
        break;
    case EWeaponType::USP:
        ShootUSP();
        break;
    case EWeaponType::Axe:
        AxeAttack();
        break;
    case EWeaponType::FirstAid:
        FirstAidInjection();
        break;
    case EWeaponType::MAX:
        break;
    default:
        break;
    }
}

void UWeaponSystemComponent::StopShooting()
{
    GetWorld()->GetTimerManager().ClearTimer(Ak47TimerHandle);
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

void UWeaponSystemComponent::FirstAidInjection()
{
    if (!bAttacking && FirstAidTotal > 0)
    {
        bAttacking = true;
        PlayFireMontage();  
        Health = 100.f;
        FirstAidTotal--;
    }
}

void UWeaponSystemComponent::ReloadAk47()
{
    if (Ak47_CurrentMagAmmo < Ak47_MaxMagAmmo && Ak47_TotalAmmo > 0)
    {
        bIsReloading = true;
        StopShooting();
        PlayReloadMontage();
        Ak47_NeededAmmo = Ak47_MaxMagAmmo - Ak47_CurrentMagAmmo;
        if (Ak47_NeededAmmo < Ak47_TotalAmmo)
        {
            Ak47_CurrentMagAmmo += Ak47_NeededAmmo;
            Ak47_TotalAmmo -= Ak47_NeededAmmo;
        }
        else
		{
			Ak47_CurrentMagAmmo += Ak47_TotalAmmo;
			Ak47_TotalAmmo = 0;
		}
    }    
}

void UWeaponSystemComponent::ReloadUSP()
{
    if (USP_CurrentMagAmmo < USP_MaxMagAmmo && USP_TotalAmmo > 0)
    {
        bIsReloading = true;
        StopShooting();
        PlayReloadMontage();
        USP_NeededAmmo = USP_MaxMagAmmo - USP_CurrentMagAmmo;
        if (USP_NeededAmmo < USP_TotalAmmo)
        {
            USP_CurrentMagAmmo += USP_NeededAmmo;
            USP_TotalAmmo -= USP_NeededAmmo;
        }
        else
        {
            USP_CurrentMagAmmo += USP_TotalAmmo;
            USP_TotalAmmo = 0;
        }
    }
}

void UWeaponSystemComponent::ReloadWeapon()
{
    switch (CharacterRef->CurrentWeapon)
    {
    case EWeaponType::Ak47:
        ReloadAk47();
        break;
    case EWeaponType::USP:
        ReloadUSP();
        break;
    case EWeaponType::Axe:
        break;
    case EWeaponType::FirstAid:
        break;
    case EWeaponType::MAX:
        break;
    default:
        break;
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
    case EWeaponType::FirstAid:
		CharacterFireMontage = FirstAidCharacterInjectionMontage;
		GunFireAnimation = FirstAidGunInjectionAnimation;
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

void UWeaponSystemComponent::PlayReloadMontage()
{
    UAnimMontage* CharacterReloadMontage = nullptr;
    UAnimationAsset* GunReloadAnimation = nullptr;
    switch (CharacterRef->CurrentWeapon)
    {
    case EWeaponType::USP:
        CharacterReloadMontage = USPCharacterReloadMontage;
        GunReloadAnimation = USPGunReloadAnimation;
        break;
    case EWeaponType::Ak47:
        CharacterReloadMontage = Ak47CharacterReloadMontage;
        GunReloadAnimation = Ak47GunReloadAnimation;
        break;
    case EWeaponType::Axe:
        break;
    case EWeaponType::FirstAid:
        break;
    default:
        break;
    }

    if (FPSAnimInstance && CharacterReloadMontage && !FPSAnimInstance->Montage_IsPlaying(CharacterReloadMontage))
    {
        FPSAnimInstance->Montage_Play(CharacterReloadMontage);
    }

    if (CharacterRef->GunMesh && GunReloadAnimation)
    {
        CharacterRef->GunMesh->PlayAnimation(GunReloadAnimation, false);
    }
}

void UWeaponSystemComponent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if(Montage == USPCharacterFireMontage ||
	   Montage == Ak47CharacterFireMontage ||
	   Montage == AxeCharacterFireMontage ||
	   Montage == FirstAidCharacterInjectionMontage)
	{
		bAttacking = false;
	}
	else if (Montage == Ak47CharacterReloadMontage ||
             Montage == USPCharacterReloadMontage)
	{
		bIsReloading = false;
	}
}

