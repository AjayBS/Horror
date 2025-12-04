// Fill out your copyright notice in the Description page of Project Settings.


#include "HGGameInstance.h"
#include "Managers/HGWorldSubsystem.h"

UHGGameInstance::UHGGameInstance()
{
	EmotionStates.Add(EEmotionsData::FirstBeat, false);
	EmotionStates.Add(EEmotionsData::Anger, false);
	EmotionStates.Add(EEmotionsData::Envy, false);
	EmotionStates.Add(EEmotionsData::Greed, false);
	EmotionStates.Add(EEmotionsData::Pride, false);
}

void UHGGameInstance::SetEmotionValue(EEmotionsData Emotion, bool bValue)
{
	if (Emotion != EEmotionsData::FirstBeat)
	{
		if (bValue)
		{
			EmotionStates[EEmotionsData::FirstBeat] = false;
		}
	}

	EmotionStates[Emotion] = bValue;
}
