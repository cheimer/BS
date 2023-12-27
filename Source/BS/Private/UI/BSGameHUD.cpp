// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSGameHUD.h"
#include "UI/BSBaseWidget.h"

void ABSGameHUD::BeginPlay()
{
	Super::BeginPlay();

	Widgets.Add(EGameWidgetMode::Battle, CreateWidget<UBSBaseWidget>(GetWorld(), BattleWidgetClass));
	Widgets.Add(EGameWidgetMode::Inventory, CreateWidget<UBSBaseWidget>(GetWorld(), InventoryWidgetClass));
	Widgets.Add(EGameWidgetMode::Pause, CreateWidget<UBSBaseWidget>(GetWorld(), PauseWidgetClass));
	Widgets.Add(EGameWidgetMode::GameEnd, CreateWidget<UBSBaseWidget>(GetWorld(), GameEndWidgetClass));

	for (auto WidgetPair : Widgets)
	{
		UBSBaseWidget* WidgetIndex = WidgetPair.Value;
		if (!WidgetIndex) continue;

		WidgetIndex->AddToViewport();
		WidgetIndex->SetVisibility(ESlateVisibility::Hidden);
	}

	CurrentWidget = Widgets[EGameWidgetMode::Battle];
	CurrentWidget->SetVisibility(ESlateVisibility::Visible);

}

void ABSGameHUD::ChangeWidget(EGameWidgetMode NewWidget)
{
	if (!Widgets.Contains(NewWidget)) return;

	if (Widgets[NewWidget] == CurrentWidget && NewWidget != EGameWidgetMode::Battle)
	{
		ChangeWidget(EGameWidgetMode::Battle);
	}
	else if (Widgets[NewWidget] != CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
		CurrentWidget = Widgets[NewWidget];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);

		CurrentWidget->BeginFunc();
	}

}
