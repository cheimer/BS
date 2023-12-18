// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BSGameHUD.generated.h"


UCLASS()
class BS_API ABSGameHUD : public AHUD
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

};
