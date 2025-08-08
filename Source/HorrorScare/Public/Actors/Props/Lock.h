// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lock.generated.h"

class ALockDial;

UCLASS()
class HORRORSCARE_API ALock : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> LockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Lock")
	TSubclassOf<ALockDial> LockDialClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	TArray<FName> SocketNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	TArray<int32> LockCombination;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ALockDial>> LockDials;

	// Sets default values for this actor's properties
	ALock();

	UFUNCTION(BlueprintCallable, Category="Lock")
	bool CheckCode();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	bool bIsUnlocked = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
