// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "GameFramework/Character.h"
#include "BSEnemyCharacter.generated.h"

class UAnimMontage;
class UBehaviorTree;
class UBSHealthComponent;
class UBSItemDropComponent;

UCLASS()
class BS_API ABSEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABSEnemyCharacter();

	virtual void PlayAttackAnim();

	float GetHealth() { return States.Health; }

	bool IsDead();	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FEnemyState States;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnDeath(AActor* DeathActor);

	UFUNCTION()
	virtual void OnAttack(AActor* Attacker);

	float GetDistancePlayer() const;

	void SetEnemyDefault();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBSItemDropComponent* ItemDropComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	TArray<UAnimMontage*> AttackAnims;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditDefaultsOnly, Category = "State")
	FName EnemyName = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	bool bUseDataTableEnemy = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	class UDataTable* DTEnemy;

private:
	void SetActorRotationPlayer();
	void DeathAnimEnd();

};
