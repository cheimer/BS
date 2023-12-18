// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSPlayerAttackComponent.h"
#include "Player/Weapon/BSPlayerWeapon.h"
#include "BSCoreTypes.h"
#include "TimerManager.h"
#include "NiagaraComponent.h"

UBSPlayerAttackComponent::UBSPlayerAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	AttackMaterialSetting();
}

void UBSPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetAttackTypesTimer();
}

void UBSPlayerAttackComponent::PlayerAttack(ABSPlayerWeapon* PlayerWeapon, FAttackState WeaponState)
{
	if (WeaponState.AttackLevel <= 0) return;

	AActor* Player = GetOwner();
	if (!Player) return;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Player->GetActorLocation() + Player->GetActorForwardVector() * 5.0f); // Arrow 위치 조정
	SpawnTransform.SetRotation(Player->GetActorRotation().Quaternion());

	int WeaponIndex = AttackTypeToIndex(WeaponState.AttackType);
	if (WeaponIndex == -1) return;

	if (!GetWorld()) return;
	ABSPlayerWeapon* SpawnedWeapon = GetWorld()->SpawnActorDeferred<ABSPlayerWeapon>(PlayerWeaponClass[WeaponIndex], SpawnTransform);
	if (SpawnedWeapon)
	{
		SpawnedWeapon->SetOwner(Player);
		SpawnedWeapon->WeaponSetting(CurrentAttackMaterial, WeaponData[WeaponIndex]);
		SpawnedWeapon->FinishSpawning(SpawnTransform);

		if (IsDrawDebugSphere)
		{
			SpawnedWeapon->DrawWeaponCollision(DebugSphereColor);
		}
	}

}

void UBSPlayerAttackComponent::SetAttackTypesTimer()
{
	if (PlayerWeaponClass.Num() != WeaponData.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Setting ERROR"));
		return;
	}

	for (int Index = 0; Index < PlayerWeaponClass.Num(); Index++)
	{
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("PlayerAttack"), PlayerWeaponClass[Index], WeaponData[Index]);

		FTimerHandle TimerHandler;
		GetWorld()->GetTimerManager().SetTimer(TimerHandler, TimerDel, WeaponData[Index].AttackDelay, true);
	}
}

int UBSPlayerAttackComponent::AttackTypeToIndex(EAttackType AttackType)
{
	EAttackType CurrentAttackType = EAttackType::Melee;

	for (int Index = 0; Index < PlayerWeaponClass.Num(); Index++)
	{
		if (CurrentAttackType == AttackType)
		{
			return Index;
		}
		else
		{
			CurrentAttackType = static_cast<EAttackType>(static_cast<int>(CurrentAttackType) + 1);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Weapon Mismatch"));
	return -1;
}

void UBSPlayerAttackComponent::AttackMaterialSetting()
{
	AttackMaterialLevel.Add(EAttackMaterial::Dark, 1);
	AttackMaterialLevel.Add(EAttackMaterial::Shine, 1);
	AttackMaterialLevel.Add(EAttackMaterial::Fire, 1);
	AttackMaterialLevel.Add(EAttackMaterial::Ice, 1);
	AttackMaterialLevel.Add(EAttackMaterial::Water, 1);
	AttackMaterialLevel.Add(EAttackMaterial::Thunder, 1);
	CurrentAttackMaterial = EAttackMaterial::Thunder;
}

float UBSPlayerAttackComponent::GetWeaponDamage(EAttackType AttackType)
{
	int index = AttackTypeToIndex(AttackType);
	if (index < 0) return -1;

	auto MaterialDamage = *AttackMaterialLevel.Find(CurrentAttackMaterial) * WeaponData[index].DamageDefault;

	return WeaponData[index].DamageDefault * WeaponData[index].AttackLevel + MaterialDamage;
}

void UBSPlayerAttackComponent::ChangeMaterialSequence()
{
	int NextMaterialIndex = static_cast<int>(CurrentAttackMaterial) + 1;
	if (NextMaterialIndex == AttackMaterialLevel.Num())
	{
		NextMaterialIndex = 0;
	}

	CurrentAttackMaterial = static_cast<EAttackMaterial>(NextMaterialIndex);

}

void UBSPlayerAttackComponent::AttackTypeEnforce(EAttackType AttackType)
{
	int TypeIndex = AttackTypeToIndex(AttackType);
	WeaponData[TypeIndex].AttackLevel++;

}

void UBSPlayerAttackComponent::AttackMaterialEnforce(EAttackMaterial AttackMaterial)
{
	*AttackMaterialLevel.Find(AttackMaterial) += 1;

}
