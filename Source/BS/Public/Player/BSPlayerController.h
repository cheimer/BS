// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "BSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BS_API ABSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void InputInventory(const FInputActionValue& Value);
	void InputPause(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputMappingContext* ControllerInputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* InventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* PauseAction;

private:
	class ABSGameHUD* BSHUD;

};
