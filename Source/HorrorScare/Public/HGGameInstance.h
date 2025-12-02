// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HGGameInstance.generated.h"

enum class EEmotionsData : uint8;

/**
 * 
 */
UCLASS()
class HORRORSCARE_API UHGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
	TMap<EEmotionsData, bool> EmotionStates;
	
	UHGGameInstance();

	UFUNCTION(BlueprintCallable)
	void SetEmotionValue(EEmotionsData Emotion, bool bValue);
};
