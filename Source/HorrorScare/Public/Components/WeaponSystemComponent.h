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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="USP")
	int32 USP_TotalAmmo; // Total ammo available

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_CurrentMagAmmo; // Current ammo in the USP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_MaxMagAmmo; // Maximum ammo in the USP magazine

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_NeededAmmo; // Ammo needed to reload the USP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USP")
	int32 USP_Damage; // Damage dealt by the USP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimMontage> USPCharacterFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimationAsset> USPGunFireAnimation;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void PlayUSPFireMontage(AL1_Character* CharacterRef);


};
