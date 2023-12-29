// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSHealthComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "Enemy/BSEnemyCharacter.h"
#include "World/BSGameInstance.h"
#include "World/BSGameModeBase.h"

UBSHealthComponent::UBSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
		if (const auto Player = Cast<ABSPlayerCharacter>(Owner))
		{
			MaxHealth = GameIns->PlayerMaxHealth;
			CurrentHealth = GameIns->PlayerCurrentHealth;
		}
		else if (const auto Enemy = Cast<ABSEnemyCharacter>(Owner))
		{
			MaxHealth = Enemy->States.Health * GameIns->MapLevel;
			CurrentHealth = MaxHealth;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HealthComponent On Not Player, Not Enemy"));
			check(true);
		}

		Owner->OnTakeAnyDamage.AddDynamic(this, &UBSHealthComponent::OnTakeDamage);
	}

	if (const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnGameEndSignature.AddUObject(this, &UBSHealthComponent::OnGameEnd);
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

void UBSHealthComponent::OnGameEnd(bool bClear)
{
	if (!GetOwner()) return;

	const auto Player = Cast<ABSPlayerCharacter>(GetOwner());
	if (!Player) return;

	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	if (bClear)
	{
		GameIns->PlayerCurrentHealth = CurrentHealth + (MaxHealth - CurrentHealth) * 0.5f;
	}

}

void UBSHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}

void UBSHealthComponent::SetHealthFull()
{
	SetHealth(MaxHealth);
}
