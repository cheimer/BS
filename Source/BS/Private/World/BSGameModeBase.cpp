// Copyright Epic Games, Inc. All Rights Reserved.


#include "BSGameModeBase.h"
#include "Player/BSPlayerCharacter.h"
#include "Player/BSPlayerController.h"
#include "Enemy/BSEnemyCharacter.h"
#include "UI/BSGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "World/BSGameInstance.h"

ABSGameModeBase::ABSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ABSPlayerCharacter::StaticClass();
	PlayerControllerClass = ABSPlayerController::StaticClass();
	HUDClass = ABSGameHUD::StaticClass();
}

void ABSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bClear = false;

	GameStartTime = GetWorld()->GetTimeSeconds();

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ABSGameModeBase::SpawnEnemyTimer, 2.0f, true);

	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	MapMaterial = GameIns->MapMaterial;
}	

void ABSGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RemainTime = FMath::Clamp(TimeLimit + GameStartTime - GetWorld()->GetTimeSeconds(), 0.0f, TimeLimit);

	if (FMath::IsNearlyZero(RemainTime))
	{
		TimeOver();
	}

}

void ABSGameModeBase::SpawnEnemyTimer()
{
	UBSGameInstance* GameInst = Cast<UBSGameInstance>(GetGameInstance());

	FVector SpawnLocation;
	for (auto Enemy : GameInst->EnemyList)
	{
		for (int SpawnIndex = 0; SpawnIndex < Enemy.Value; SpawnIndex++)
		{
			SpawnLocation = CalcSpawnLocation();
			FRotator SpawnRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
			auto SpawnedEnemy = GetWorld()->SpawnActor<ABSEnemyCharacter>(EnemyListClass[Enemy.Key], SpawnLocation, SpawnRotator);
			EnemyNum++;
		}
	}

	if (EnemyNum > MaxEnemyNum)
	{
		EnemyOver();
	}

}

FVector ABSGameModeBase::CalcSpawnLocation()
{
	if (!GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawn()) return FVector::ZeroVector;
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	float MaxSpawnRadius = 2000.0f;
	float MinSpawnRadius = 500.0f;
	FVector2D SpawnLocation2D = FMath::RandPointInCircle(MaxSpawnRadius);

	while (true)
	{
		if (SpawnLocation2D.Size() > MinSpawnRadius)
		{
			SpawnLocation2D.X += PlayerLocation.X;
			SpawnLocation2D.Y += PlayerLocation.Y;
			if (MapSize.IsInsideOrOn(SpawnLocation2D))
			{
				break;
			}
		}
		SpawnLocation2D = FMath::RandPointInCircle(MaxSpawnRadius);
	}
	
	FVector SpawnLocation(SpawnLocation2D.X, SpawnLocation2D.Y, PlayerLocation.Z);

	return SpawnLocation;
}

void ABSGameModeBase::TimeOver()
{
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller) return;

	const auto GameHUD = Cast<ABSGameHUD>(Controller->GetHUD());
	if (!GameHUD) return;

	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	bClear = true;
	OnGameEndSignature.Broadcast(bClear);

	int MaterialRandNum = FMath::RandRange(0, GameIns->MaterialLevel.Num() - 1);
	GameIns->MapMaterial = StaticCast<EAttackMaterial>(MaterialRandNum);
	GameIns->MapLevel++;

	SpawnEnemyNumAdd();
	GameHUD->ChangeWidget(EGameWidgetMode::GameEnd);

}

void ABSGameModeBase::EnemyOver()
{
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller) return;

	const auto GameHUD = Cast<ABSGameHUD>(Controller->GetHUD());
	if (!GameHUD) return;

	bClear = false;
	OnGameEndSignature.Broadcast(bClear);

	GameHUD->ChangeWidget(EGameWidgetMode::GameEnd);
}

void ABSGameModeBase::PlayerDeath()
{
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller) return;

	const auto GameHUD = Cast<ABSGameHUD>(Controller->GetHUD());
	if (!GameHUD) return;

	bClear = false;
	OnGameEndSignature.Broadcast(bClear);

	GameHUD->ChangeWidget(EGameWidgetMode::GameEnd);
}

void ABSGameModeBase::EnemyDeath()
{
	EnemyNum--;
}

void ABSGameModeBase::SpawnEnemyNumAdd()
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	if (GameIns->MapLevel % SpawnEnemyAddRound == 0)
	{
		for (auto EnemyListIndex : GameIns->EnemyList)
		{
			if (GameIns->EnemyList[EnemyListIndex.Key] != 0)
			{
				GameIns->EnemyList[EnemyListIndex.Key] += 1;
			}
		}
	}
}

float ABSGameModeBase::GetRemainTime()
{
	return RemainTime;
}

bool ABSGameModeBase::IsAdvantageType(EAttackMaterial Attacker, EAttackMaterial Defender)
{
	if (Attacker == EAttackMaterial::Dark && Defender == EAttackMaterial::Shine)
		return true;
	if (Attacker == EAttackMaterial::Shine && Defender == EAttackMaterial::Dark)
		return true;
	if (Attacker == EAttackMaterial::Fire && Defender == EAttackMaterial::Ice)
		return true;
	if (Attacker == EAttackMaterial::Ice && Defender == EAttackMaterial::Thunder)
		return true;
	if (Attacker == EAttackMaterial::Thunder && Defender == EAttackMaterial::Water)
		return true;
	if (Attacker == EAttackMaterial::Water && Defender == EAttackMaterial::Fire)
		return true;

	return false;
}
