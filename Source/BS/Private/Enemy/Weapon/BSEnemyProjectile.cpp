// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Weapon/BSEnemyProjectile.h"
#include "Enemy/BSEnemyCharacter.h"
#include "Player/BSPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ABSEnemyProjectile::ABSEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->InitialSpeed = ProjectileSpeed;

}

void ABSEnemyProjectile::BeginPlay()
{
	Super::BeginPlay(); 

	MovementComponent->Velocity = GetActorForwardVector() * MovementComponent->InitialSpeed;
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABSEnemyProjectile::OnArrowHit);
	
	SetLifeSpan(5.0f);
	
	CreateTime = GetWorld()->GetTimeSeconds();

}

void ABSEnemyProjectile::OnArrowHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABSPlayerCharacter::StaticClass()))
	{
		const auto Player = Cast<ABSPlayerCharacter>(OtherActor);
		const auto Enemy = Cast<ABSEnemyCharacter>(GetOwner());
		if (!Player || !Enemy) return;

		Player->TakeDamage(Enemy->States.Damage, FDamageEvent::FDamageEvent(), Enemy->GetController(), this);

		Destroy();
	}
}

UNiagaraComponent* ABSEnemyProjectile::SpawnEffectFX()
{
	if (!EffectFX) return nullptr;

	return UNiagaraFunctionLibrary::SpawnSystemAttached(EffectFX, MeshComponent, "", 
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}
