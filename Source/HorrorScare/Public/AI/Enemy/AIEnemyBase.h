// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIEnemyBase.generated.h"

UCLASS()
class HORRORSCARE_API AAIEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoints")
	TArray<TObjectPtr<AActor>> Waypoints;

	int32 CurrentWaypointIndex;

	AActor* SetNewWaypointData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
