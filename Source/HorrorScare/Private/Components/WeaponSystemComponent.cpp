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
    FVector Start;
    FVector End;
    FHitResult HitResult;

    FRotator PlayerRot;
    PlayerCharacter->GetController()->GetPlayerViewPoint(Start, PlayerRot);
    End = Start + PlayerRot.Vector() * USP_Range;

    // Line trace parameters
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(PlayerCharacter); // Ignore self

    // Perform the line trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        TraceParams
    );

    PlayUSPFireMontage(PlayerCharacter);
}


// Called when the game starts
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UWeaponSystemComponent::PlayUSPFireMontage(AL1_Character* CharacterRef)
{
    if(!USPCharacterFireMontage && !USPGunFireAnimation) return;

    UAnimInstance* FPSAnimInstance = CharacterRef->FirstPersonMesh->GetAnimInstance();
    if (FPSAnimInstance && !FPSAnimInstance->Montage_IsPlaying(USPCharacterFireMontage))
    {
        FPSAnimInstance->Montage_Play(USPCharacterFireMontage);
    }

    UAnimInstance* GunAnimInstance = CharacterRef->GunMesh->GetAnimInstance();
    if (CharacterRef->GunMesh)
    {
        CharacterRef->GunMesh->PlayAnimation(USPGunFireAnimation, false);
    }
}

