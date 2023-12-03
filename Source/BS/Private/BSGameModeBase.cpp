// Copyright Epic Games, Inc. All Rights Reserved.


#include "BSGameModeBase.h"
#include "Player/BSPlayerCharacter.h"
#include "Player/BSPlayerController.h"
#include "Kismet/GameplayStatics.h"

ABSGameModeBase::ABSGameModeBase()
{
	DefaultPawnClass = ABSPlayerCharacter::StaticClass();
	PlayerControllerClass = ABSPlayerController::StaticClass();

}

AActor* ABSGameModeBase::GetBSPlayerCharacter()
{
	ABSPlayerCharacter* BSPlayer = Cast<ABSPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (BSPlayer)
	{
		return BSPlayer;
	}
	else
	{
		return nullptr;
	}

}