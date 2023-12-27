// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BSGameHUD.generated.h"

UENUM(BlueprintType)
enum class EGameWidgetMode : uint8
{
	Battle = 0,
	Inventory,
	Pause, 
	GameEnd
};

UCLASS()
class BS_API ABSGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeWidget(EGameWidgetMode NewWidget);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BattleWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameEndWidgetClass;

private:
	TMap<EGameWidgetMode, class UBSBaseWidget*> Widgets;

	class UBSBaseWidget* CurrentWidget = nullptr;

};
