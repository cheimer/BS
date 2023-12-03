// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSAIPerceptionComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "Perception/AISense_Sight.h"

UBSAIPerceptionComponent::UBSAIPerceptionComponent()
{

}

AActor* UBSAIPerceptionComponent::GetPlayerActor() const
{
	TArray<AActor*> PerceiveActors;

	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);

	if (PerceiveActors.Num() == 0)
	{
		return nullptr;
	}

	for (const auto PerceiveActor : PerceiveActors) // return only first player
	{
		if (Cast<ABSPlayerCharacter>(PerceiveActor))
		{
			return PerceiveActor;
		}
	}

	return nullptr;
}
