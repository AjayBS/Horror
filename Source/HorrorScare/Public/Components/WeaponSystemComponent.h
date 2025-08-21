// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Managers/HGWorldSubsystem.h"
#include "WeaponSystemComponent.generated.h"

class AL1_Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSCARE_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSystemComponent();
	void ShootWeapon();
	void StopShooting();
	void ReloadWeapon();
	float GetAk47ShootRate() const { return Ak47_ShootRate; }
	bool CanEquip() const { return !bAttacking; }
	bool IsReloading() const { return bIsReloading; }
	bool IsWeaponPicked(int32 Index) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="USP")
	int32 USP_TotalAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_CurrentMagAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_MaxMagAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_NeededAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ak47")
	int32 Ak47_TotalAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ak47")
	int32 Ak47_CurrentMagAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ak47")
	int32 Ak47_MaxMagAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ak47")
	int32 Ak47_NeededAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ak47")
	int32 Ak47_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ak47")
	int32 Ak47_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ak47")
	float Ak47_ShootRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FirstAid")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FirstAid")
	int32 FirstAidTotal = 3;

	bool bAttacking = false;
	bool bIsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> USPCharacterFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> USPGunFireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> Ak47CharacterFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> Ak47GunFireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> AxeCharacterFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> FirstAidCharacterInjectionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> FirstAidGunInjectionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> Ak47CharacterReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> Ak47GunReloadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> USPCharacterReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> USPGunReloadAnimation;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TObjectPtr<AL1_Character> CharacterRef;
	TObjectPtr<UAnimInstance> FPSAnimInstance;
	FTimerHandle Ak47TimerHandle;

	void ShootUSP();

	UFUNCTION()
	void ShootAk47();

	void AxeAttack();
	void FirstAidInjection();

	void ReloadAk47();
	void ReloadUSP();

	void WeaponLineTrace();
	void PlayFireMontage();
	void PlayReloadMontage();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
