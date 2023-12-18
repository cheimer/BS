// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/BSPlayerWeapon.h"
#include "Player/BSPlayerCharacter.h"
#include "Enemy/BSEnemyCharacter.h"
#include "BSComponent/BSPlayerAttackComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


ABSPlayerWeapon::ABSPlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);

	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->ProjectileGravityScale = 0.0f;

}

void ABSPlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABSPlayerWeapon::OnWeaponHit);

	CreateTime = GetWorld()->GetTimeSeconds();

}

void ABSPlayerWeapon::OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABSEnemyCharacter::StaticClass()))
	{
		const auto Player = Cast<ABSPlayerCharacter>(GetOwner());
		const auto Enemy = Cast<ABSEnemyCharacter>(OtherActor);
		if (!Player || !Enemy) return;
		
		float Damage = Player->GetComponentByClass<UBSPlayerAttackComponent>()->GetWeaponDamage(AttackType);

		Enemy->TakeDamage(Damage, FDamageEvent::FDamageEvent(), Player->GetController(), this);

		if (AttackState.EnemyHitNum > 0)
		{
			AttackState.EnemyHitNum -= 1;

			if (AttackState.EnemyHitNum == 0)
			{
				Destroy();
			}
		}
	}
}

void ABSPlayerWeapon::WeaponSetting(EAttackMaterial CurrentAttackMaterial, FAttackState CurrentAttackState)
{
	if (!AttackMaterial.Find(CurrentAttackMaterial))
		return;

	FXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(AttackMaterial[CurrentAttackMaterial], CollisionComponent, "",
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
	
	FXComponent->SetPaused(false);
	FXComponent->SetVisibility(true, true);
	
	AttackState = CurrentAttackState;

	SetDefaultOption();

}

void ABSPlayerWeapon::DrawWeaponCollision(FColor DebugSphereColor)
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionComponent->GetScaledSphereRadius(), 16, FColor::Black, false, 1.0f);
}

AActor* ABSPlayerWeapon::FindClosestEnemy()
{
	FVector CurrentLocation = GetActorLocation();
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(WeaponLength);

	TArray<FHitResult> HitInfos;
	bool IsHit = GetWorld()->SweepMultiByObjectType(HitInfos, CurrentLocation, CurrentLocation, FQuat::Identity,
		FCollisionObjectQueryParams::AllObjects, CollisionSphere);

	if (IsHit)
	{
		AActor* ClosestEnemy = nullptr;
		float MinDistance = WeaponLength;

		for (FHitResult& HitInfo : HitInfos)
		{
			if (HitInfo.GetActor()->IsA(ABSEnemyCharacter::StaticClass()))
			{
				float Distance = FVector::Distance(CurrentLocation, HitInfo.GetActor()->GetActorLocation());

				if (Distance < MinDistance && !Cast<ABSEnemyCharacter>(HitInfo.GetActor())->IsDead())
				{
					ClosestEnemy = HitInfo.GetActor();
					MinDistance = Distance;
				}
			}
		}

		return ClosestEnemy;
	}

	return nullptr;
}
