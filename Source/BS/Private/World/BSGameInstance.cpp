// Fill out your copyright notice in the Description page of Project Settings.


#include "World/BSGameInstance.h"
#include "BSCoreTypes.h"

UBSGameInstance::UBSGameInstance()
{
	EnemyListDefaultSetting();


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
