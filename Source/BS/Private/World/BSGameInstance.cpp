// Fill out your copyright notice in the Description page of Project Settings.


#include "World/BSGameInstance.h"
#include "BSCoreTypes.h"

UBSGameInstance::UBSGameInstance()
{
	EnemyListDefaultSetting();
	MapLevel = 1;
	TypeLevelDefaultSetting();
	MaterialLevelDefaultSetting();
	MaterialNumDefaultSetting();
	CoinNum = 0;
	RestoreHealthCost = MinRestoreCost;
	PlayerCurrentHealth = PlayerMaxHealth;
	CurrentMaterial = EAttackMaterial::Thunder;
	MapMaterial = StaticCast<EAttackMaterial>(FMath::RandRange(0, 5));
}

void UBSGameInstance::SetEnemyList(EEnemyList Enemy, int32 EnemyNum)
{
	if (!EnemyList.Find(Enemy)) return;

	EnemyList[Enemy] = EnemyNum;

}

void UBSGameInstance::EnemyListDefaultSetting()
{
	EnemyList.Add(EEnemyList::Ghoul, 0);
	EnemyList.Add(EEnemyList::Goblin, 0);
	EnemyList.Add(EEnemyList::Rich, 0);
	EnemyList.Add(EEnemyList::SkelBow, 0);
	EnemyList.Add(EEnemyList::SkelSword, 0);
	EnemyList.Add(EEnemyList::Zombie, 0);
}

void UBSGameInstance::TypeLevelDefaultSetting()
{
	TypeLevel.Add(EAttackType::Melee, 1);
	TypeLevel.Add(EAttackType::Arrow, 1);
	TypeLevel.Add(EAttackType::Spell, 1);
}

void UBSGameInstance::MaterialLevelDefaultSetting()
{
	MaterialLevel.Add(EAttackMaterial::Dark, 1);
	MaterialLevel.Add(EAttackMaterial::Shine, 1);
	MaterialLevel.Add(EAttackMaterial::Thunder, 1);
	MaterialLevel.Add(EAttackMaterial::Ice, 1);
	MaterialLevel.Add(EAttackMaterial::Fire, 1);
	MaterialLevel.Add(EAttackMaterial::Water, 1);
}

void UBSGameInstance::MaterialNumDefaultSetting()
{
	MaterialNum.Add(EAttackMaterial::Dark, 0);
	MaterialNum.Add(EAttackMaterial::Shine, 0);
	MaterialNum.Add(EAttackMaterial::Thunder, 0);
	MaterialNum.Add(EAttackMaterial::Ice, 0);
	MaterialNum.Add(EAttackMaterial::Fire, 0);
	MaterialNum.Add(EAttackMaterial::Water, 0);
}
