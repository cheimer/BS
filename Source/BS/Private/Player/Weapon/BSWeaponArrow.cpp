// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/BSWeaponArrow.h"
#include "Enemy/BSEnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ABSWeaponArrow::ABSWeaponArrow()
{
	AttackType = EAttackType::Arrow;
}

void ABSWeaponArrow::SetDefaultOption()
{
	MovementComponent->InitialSpeed = ArrowSpeed;
	
	SetLifeSpan(LifeTime);

	SetArrowLevelAdd();

	auto TargetEnemy = FindClosestEnemy();

	if (TargetEnemy)
	{
		FVector Direction = TargetEnemy->GetActorLocation() - GetActorLocation();
		Direction.Normalize();

		SetActorRotation(Direction.ToOrientationQuat());

	}
}

void ABSWeaponArrow::SetArrowLevelAdd()
{
	if (AttackState.EnemyHitNum == -1)
	{
		return;
	}
	else
	{
		AttackState.EnemyHitNum += AttackState.AttackLevel / HitNumAddLevel;
	}

}
