// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSCoreTypes.h"
#include "BSPlayerWeapon.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class ABSEnemyCharacter;

UCLASS()
class BS_API ABSPlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:		
	ABSPlayerWeapon();

	void WeaponSetting(EAttackMaterial CurrentAttackMaterial, FAttackState CurrentAttackState);

	EAttackType GetAttackType() { return AttackType; }

	void DrawWeaponCollision(FColor DebugSphereColor);

protected:
	virtual void BeginPlay() override;

	virtual void SetDefaultOption() { ; }

	AActor* FindClosestEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* FXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Types")
	EAttackType AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Types")
	TMap<EAttackMaterial, UNiagaraSystem*> AttackMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float WeaponLength = 1000.0f;

	FAttackState AttackState;

private:
	UFUNCTION()
	void OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float CreateTime;

};
