// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSHealthComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "Enemy/BSEnemyCharacter.h"

UBSHealthComponent::UBSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UBSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		if (const auto Player = Cast<ABSPlayerCharacter>(Owner))
		{
			MaxHealth = Player->GetHealth();
		}
		else if (const auto Enemy = Cast<ABSEnemyCharacter>(Owner))
		{
			MaxHealth = Enemy->GetHealth();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Player, Not Enemy"));
		}

		CurrentHealth = MaxHealth;

		Owner->OnTakeAnyDamage.AddDynamic(this, &UBSHealthComponent::OnTakeDamage);

	}

}

void UBSHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0)
		return;

	SetHealth(CurrentHealth - Damage);

	if (IsDead())
	{
		OnDeathSignature.Broadcast(GetOwner());
	}
	
}

void UBSHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}
