// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystemComponent.generated.h"

class AL1_Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSCARE_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSystemComponent();
	void ShootUSP();
	void ShootAk47();
	float GetAk47ShootRate() const { return Ak47_ShootRate; }

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> USPCharacterFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> USPGunFireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> Ak47CharacterFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> Ak47GunFireAnimation;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void WeaponLineTrace(AL1_Character* CharacterRef);
	void PlayFireMontage(AL1_Character* CharacterRef);


};
