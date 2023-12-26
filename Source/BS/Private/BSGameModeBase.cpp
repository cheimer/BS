// Copyright Epic Games, Inc. All Rights Reserved.


#include "BSGameModeBase.h"
#include "Player/BSPlayerCharacter.h"
#include "Player/BSPlayerController.h"
#include "UI/BSGameHUD.h"
#include "Kismet/GameplayStatics.h"

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

	GameStartTime = GetWorld()->GetTimeSeconds();

}

void ABSGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RemainTime = FMath::Clamp(TimeLimit + GameStartTime - GetWorld()->GetTimeSeconds(), 0.0f, TimeLimit);

	if (FMath::IsNearlyZero(RemainTime))
	{
		TimeOver();
	}
	else
	{

	}
}

void ABSGameModeBase::TimeOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Time Over TEMP"));

}

float ABSGameModeBase::GetRemainTime()
{
	return RemainTime;
}

void ABSGameModeBase::PlayerDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerDeath"));
}
