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

	SetSpellLevelAdd();

	CollisionComponent->SetSphereRadius(AttackState.SpellSize);

	float SizeTimes = AttackState.SpellSize / AttackState.SpellDefaultSize;
	FXComponent->SetWorldScale3D(FVector(SizeTimes, SizeTimes, 1.0f));

}

void ABSWeaponSpell::SetSpellLevelAdd()
{
	if (AttackState.SpellSize / AttackState.SpellDefaultSize >= 3.0f)
	{
		return;
	}
	else
	{
		AttackState.SpellSize = AttackState.SpellSize * (1.0f + 0.1f * AttackState.AttackLevel / SizeAddLevel);
	}
}
