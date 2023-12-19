// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BSGameHUD.generated.h"

UENUM(BlueprintType)
enum class EWidgetMode : uint8
{
	Battle = 0,
	Inventory,
	Pause
};

UCLASS()
class BS_API ABSGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeWidget(EWidgetMode NewWidget);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BattleWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

private:
	TMap<EWidgetMode, class UBSBaseWidget*> Widgets;

	class UBSBaseWidget* CurrentWidget = nullptr;

};
