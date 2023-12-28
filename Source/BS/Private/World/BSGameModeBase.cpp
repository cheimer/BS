// Copyright Epic Games, Inc. All Rights Reserved.


#include "BSGameModeBase.h"
#include "Player/BSPlayerCharacter.h"
#include "Player/BSPlayerController.h"
#include "Enemy/BSEnemyCharacter.h"
#include "UI/BSGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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

	isClear = false;

	GameStartTime = GetWorld()->GetTimeSeconds();

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ABSGameModeBase::SpawnEnemyTimer, 2.0f, true);

	SetMapMaterialRand();
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
		}
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

	FVector SpawnLocation = UKismetMathLibrary::Conv_Vector2DToVector(SpawnLocation2D);
	SpawnLocation.Z = PlayerLocation.Z;

	return SpawnLocation;
}

void ABSGameModeBase::SetMapMaterialRand()
{
	int32 Index = FMath::RandRange(0, 5);
	MapMaterial = StaticCast<EAttackMaterial>(Index);
}

void ABSGameModeBase::TimeOver()
{
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller) return;

	const auto GameHUD = Cast<ABSGameHUD>(Controller->GetHUD());
	if (!GameHUD) return;

	isClear = true;
	GameHUD->ChangeWidget(EGameWidgetMode::GameEnd);

}

float ABSGameModeBase::GetRemainTime()
{
	return RemainTime;
}

void ABSGameModeBase::PlayerDeath()
{
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller) return;

	const auto GameHUD = Cast<ABSGameHUD>(Controller->GetHUD());
	if (!GameHUD) return;

	isClear = false;
	GameHUD->ChangeWidget(EGameWidgetMode::GameEnd);
}
