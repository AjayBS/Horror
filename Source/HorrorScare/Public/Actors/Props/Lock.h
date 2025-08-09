// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lock.generated.h"

class ALockDial;
class UBoxComponent;

UCLASS()
class HORRORSCARE_API ALock : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> LockMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Lock")
	TSubclassOf<ALockDial> LockDialClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	TArray<FName> SocketNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	TArray<int32> LockCombination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	FVector BoxPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	FVector BoxExtent = FVector(32.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ALockDial>> LockDials;

	// Sets default values for this actor's properties
	ALock();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Lock")
	void BP_CheckEveryTurn();

	UFUNCTION(BlueprintCallable, Category="Lock")
	bool CheckCode();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	bool bIsUnlocked = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
