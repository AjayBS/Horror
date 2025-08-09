// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockDial.generated.h"

class ALock;

UCLASS()
class HORRORSCARE_API ALockDial : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> LockDialMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock Dial")
	float DialRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock Dial")
	bool bCanRotate = true;

	UPROPERTY(BlueprintReadOnly, Category = "Lock Dial")
	TObjectPtr<ALock> LockRef;

	ALockDial();

	UFUNCTION(BlueprintCallable, Category = "Lock Dial")
	void FindNumber();

	UFUNCTION(BlueprintCallable, Category = "Lock Dial")
	void RotateDial(bool bReverse);

	UFUNCTION(BlueprintImplementableEvent, Category = "Lock Dial")
	void BP_RotateDial();

	UFUNCTION(BlueprintImplementableEvent, Category = "Lock Dial")
	void BP_RotateDialBackwards();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	virtual void BeginPlay() override;
	void SetRandomNumber();

private:
	FTimerHandle RotateTimerHandle;
};
