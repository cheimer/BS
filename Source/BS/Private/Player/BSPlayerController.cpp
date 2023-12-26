// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BSPlayerController.h"
#include "UI/BSGameHUD.h"

// EnhancedInput
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

void ABSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	BSHUD = Cast<ABSGameHUD>(GetHUD());
	check(BSHUD);

	SetInputMode(FInputModeGameOnly());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ControllerInputMapping, 0);
	}
}

void ABSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &ABSPlayerController::InputInventory);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ABSPlayerController::InputPause);
	}

}

void ABSPlayerController::InputInventory(const FInputActionValue& Value)
{
	if (!Value.Get<bool>()) return;

	BSHUD->ChangeWidget(EGameWidgetMode::Inventory);

}

void ABSPlayerController::InputPause(const FInputActionValue& Value)
{
	if (!Value.Get<bool>()) return;

	BSHUD->ChangeWidget(EGameWidgetMode::Pause);

}
