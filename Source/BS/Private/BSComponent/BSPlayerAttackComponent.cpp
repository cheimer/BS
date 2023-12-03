// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSPlayerAttackComponent.h"
#include "Player/Weapon/BSPlayerWeapon.h"
#include "BSCoreTypes.h"
#include "TimerManager.h"
#include "NiagaraComponent.h"

UBSPlayerAttackComponent::UBSPlayerAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	AttackArrSetting();
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
		SpawnedWeapon->WeaponSetting(CurrentAttackArr, WeaponData[WeaponIndex]);
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

void UBSPlayerAttackComponent::AttackArrSetting()
{
	AttackArrLevel.Add(EAttackArr::Dark, 1);
	AttackArrLevel.Add(EAttackArr::Shine, 1);
	AttackArrLevel.Add(EAttackArr::Fire, 1);
	AttackArrLevel.Add(EAttackArr::Ice, 1);
	AttackArrLevel.Add(EAttackArr::Water, 1);
	AttackArrLevel.Add(EAttackArr::Thunder, 1);
	CurrentAttackArr = EAttackArr::Thunder;
}

float UBSPlayerAttackComponent::GetWeaponDamage(EAttackType AttackType)
{
	int index = AttackTypeToIndex(AttackType);

	//TEMP
	return WeaponData[index].DamageDefault;
}
