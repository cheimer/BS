// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BSEnemyMeleeCharacter.h"
#include "Player/BSPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"

void ABSEnemyMeleeCharacter::OnAttack(AActor* Attacker)
{
	TArray<AActor*> OverlapArr;
	GetCapsuleComponent()->GetOverlappingActors(OverlapArr);

	for (AActor* OverlapActor : OverlapArr)
	{
		if (const auto Player = Cast<ABSPlayerCharacter>(OverlapActor))
		{
			Player->TakeDamage(CalcDamage(), FDamageEvent::FDamageEvent(), GetController(), this);
		}
	}

}