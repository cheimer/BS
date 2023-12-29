// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSPlayerAttackComponent.h"
#include "Player/Weapon/BSPlayerWeapon.h"
#include "World/BSGameModeBase.h"
#include "World/BSGameInstance.h"
#include "BSCoreTypes.h"
#include "TimerManager.h"
#include "NiagaraComponent.h"
#include "Engine/DataTable.h"

UBSPlayerAttackComponent::UBSPlayerAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	check(DTWeapon);
	AttackMaterialSetting();
	AttackTypeSetting();

	SetAttackTypesTimer();

	auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->OnGameEndSignature.AddUObject(this, &UBSPlayerAttackComponent::OnGameEnd);
}

void UBSPlayerAttackComponent::OnGameEnd(bool bClear)
{
	if (bClear)
	{
		SetGameInstanceMaterialLevel();
		SetGameInstanceTypeLevel();
	}
	else
	{
		//
	}

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

float UBSPlayerAttackComponent::GetWeaponDamage(EAttackType AttackType)
{
	int index = AttackTypeToIndex(AttackType);
	if (index < 0) return -1;

	float MaterialDamage = *AttackMaterialLevel.Find(CurrentAttackMaterial) * WeaponData[index].DamageDefault;
	float TypeDamage = WeaponData[index].DamageDefault * WeaponData[index].AttackLevel;

	auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	if (GameMode->IsAdvantageType(CurrentAttackMaterial, GameMode->GetMapMaterial()))
	{
		return (TypeDamage + MaterialDamage) * 1.5f;
	}
	else
	{
		return TypeDamage + MaterialDamage;
	}
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

int UBSPlayerAttackComponent::GetAttackTypeLevel(EAttackType AttackType)
{
	return WeaponData[AttackTypeToIndex(AttackType)].AttackLevel;
}

int UBSPlayerAttackComponent::GetAttackMaterialLevel(EAttackMaterial AttackMaterial)
{
	return AttackMaterialLevel[AttackMaterial];
}

void UBSPlayerAttackComponent::AttackTypeSetting()
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	TArray<FName> AttackNames = DTWeapon->GetRowNames();

	int index = 0;
	for (FName AttackName : AttackNames)
	{
		FAttackState DTAttackState = *DTWeapon->FindRow<FAttackState>(AttackName, "");
		WeaponData.Add(DTAttackState);
		
		WeaponData[index].AttackLevel = *GameIns->TypeLevel.Find(WeaponData[index].AttackType);
		index++;
	}

}

void UBSPlayerAttackComponent::AttackMaterialSetting()
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	for (int index = 0; index < GameIns->MaterialLevel.Num(); index++)
	{
		EAttackMaterial AttackMaterial = StaticCast<EAttackMaterial>(index);
		AttackMaterialLevel.Add(AttackMaterial, *GameIns->MaterialLevel.Find(AttackMaterial));
	}

	CurrentAttackMaterial = GameIns->CurrentMaterial;
}

void UBSPlayerAttackComponent::SetGameInstanceTypeLevel()
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	for (auto AttackTypeState : WeaponData)
	{
		*GameIns->TypeLevel.Find(AttackTypeState.AttackType) = AttackTypeState.AttackLevel;
	}

}

void UBSPlayerAttackComponent::SetGameInstanceMaterialLevel()
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	for (auto AttackMaterialState : AttackMaterialLevel)
	{
		*GameIns->MaterialLevel.Find(AttackMaterialState.Key) = AttackMaterialState.Value;
	}

}
