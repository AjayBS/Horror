// Confused Minds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockDial.generated.h"

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

	ALockDial();

	UFUNCTION(BlueprintCallable, Category = "Lock Dial")
	void FindNumber();

	UFUNCTION(BlueprintCallable, Category = "Lock Dial")
	void RotateDial();

	UFUNCTION(BlueprintImplementableEvent, Category = "Lock Dial")
	void BP_RotateDial();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	virtual void BeginPlay() override;
	void SetRandomNumber();

private:
	FTimerHandle RotateTimerHandle;
};
