// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/BSWeaponSpell.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

ABSWeaponSpell::ABSWeaponSpell()
{
	AttackType = EAttackType::Spell;
}

void ABSWeaponSpell::SetDefaultOption()
{
	auto TargetEnemy = FindClosestEnemy();

	if (TargetEnemy)
	{
		SetActorLocation(TargetEnemy->GetActorLocation());
		SetLifeSpan(LifeTime);
	}
	else
	{
		FXComponent->SetVisibility(false, false);
		SetLifeSpan(0.2f);
	}

	CollisionComponent->SetSphereRadius(AttackState.AuraSize);

	float SizeTimes = AttackState.SpellSize / AttackState.SpellDefaultSize;
	FXComponent->SetWorldScale3D(FVector(SizeTimes, SizeTimes, 1.0f));

}
