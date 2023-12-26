// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BSMenuController.h"

void ABSMenuController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}
