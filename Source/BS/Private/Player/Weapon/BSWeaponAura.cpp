// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/BSWeaponAura.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"


ABSWeaponAura::ABSWeaponAura()
{
	AttackType = EAttackType::Melee;
}

void ABSWeaponAura::SetDefaultOption()
{
	SetLifeSpan(AttackState.AttackDelay);

	SetAuraLevelAdd();

	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (Player && Player->GetMesh())
	{
		CollisionComponent->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
	}

	CollisionComponent->SetSphereRadius(AttackState.AuraSize);

	float SizeTimes = AttackState.AuraSize / AttackState.AuraDefaultSize;
	FXComponent->SetWorldScale3D(FVector(SizeTimes, SizeTimes, 1.0f));
}

void ABSWeaponAura::SetAuraLevelAdd()
{
	if (AttackState.AuraSize / AttackState.AuraDefaultSize >= 3.0f)
	{
		return;
	}
	else
	{
		AttackState.AuraSize = AttackState.AuraSize * (1.0f + 0.1f * AttackState.AttackLevel / SizeAddLevel);
	}
}
