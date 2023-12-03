// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BSEnemyCharacter.h"
#include "BSEnemyRangedCharacter.generated.h"

class ABSEnemyProjectile;
class UAnimMontage;

UCLASS()
class BS_API ABSEnemyRangedCharacter : public ABSEnemyCharacter
{
	GENERATED_BODY()

public:
	ABSEnemyRangedCharacter();

	virtual void PlayAttackAnim() override;

protected:
	virtual void OnAttack(AActor* Attacker) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABSEnemyProjectile> EnemyProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Anim", meta = (ToolTip = "Weapon Mesh Need to First Child Component"))
	bool HaveWeaponAnim = false;

	UPROPERTY(EditDefaultsOnly, Category = "Anim", meta = (EditCondition = "HaveWeaponAnim"))
	UAnimMontage* WeaponAnim;

private:
	void AttackArrow(AActor* Attacker);
	void AttackSpell(AActor* Attacker);

};
