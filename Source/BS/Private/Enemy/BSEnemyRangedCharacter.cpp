// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BSEnemyRangedCharacter.h"
#include "Enemy/Weapon/BSEnemyProjectile.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABSEnemyRangedCharacter::ABSEnemyRangedCharacter()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("SKT_Bow"));
}

void ABSEnemyRangedCharacter::PlayAttackAnim()
{
	Super::PlayAttackAnim();

	if (HaveWeaponAnim)
	{
		auto Weapon = Cast<USkeletalMeshComponent>(GetMesh()->GetChildComponent(0));
		if (Weapon && WeaponAnim)
		{
			if (!Weapon->GetAnimInstance()->Montage_IsPlaying(WeaponAnim))
			{
				Weapon->GetAnimInstance()->Montage_Play(WeaponAnim);
			}
		}
	}

}

void ABSEnemyRangedCharacter::OnAttack(AActor* Attacker)
{
	if (States.AttackType == EAttackType::Arrow)
	{
		AttackArrow(Attacker);
	}
	else if (States.AttackType == EAttackType::Spell)
	{
		AttackSpell(Attacker);
	}
}

void ABSEnemyRangedCharacter::AttackArrow(AActor* Attacker)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * 5.0f);
	SpawnTransform.SetRotation(GetActorRotation().Quaternion());

	if (!GetWorld()) return;
	ABSEnemyProjectile* SpawnedArrow = GetWorld()->SpawnActorDeferred<ABSEnemyProjectile>(EnemyProjectileClass, SpawnTransform);
	if (SpawnedArrow)
	{
		SpawnedArrow->SetOwner(this);
		SpawnedArrow->FinishSpawning(SpawnTransform);
	}

}

void ABSEnemyRangedCharacter::AttackSpell(AActor* Attacker)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * 5.0f);
	SpawnTransform.SetRotation(GetActorRotation().Quaternion());

	if (!GetWorld()) return;
	ABSEnemyProjectile* SpawnedSpell = GetWorld()->SpawnActorDeferred<ABSEnemyProjectile>(EnemyProjectileClass, SpawnTransform);
	if (SpawnedSpell)
	{
		SpawnedSpell->SetOwner(this);
		UNiagaraComponent* SpellFXComponent = SpawnedSpell->SpawnEffectFX();
		if (SpellFXComponent)
		{
			SpellFXComponent->SetPaused(false);
			SpellFXComponent->SetVisibility(true, true);
		}

		SpawnedSpell->FinishSpawning(SpawnTransform);

	}


}
