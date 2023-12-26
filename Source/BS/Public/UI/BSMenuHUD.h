// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BSMenuHUD.generated.h"

UENUM(BlueprintType)
enum class EMenuWidgetMode : uint8
{
	Main = 0,
	Custom
};

UCLASS()
class BS_API ABSMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeWidget(EMenuWidgetMode NewWidget);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> CustomWidgetClass;

private:
	TMap<EMenuWidgetMode, class UBSBaseWidget*> Widgets;

	class UBSBaseWidget* CurrentWidget = nullptr;
};
