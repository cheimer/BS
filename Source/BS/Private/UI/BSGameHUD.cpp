// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSGameHUD.h"
#include "UI/BSBaseWidget.h"

void ABSGameHUD::BeginPlay()
{
	Super::BeginPlay();

	Widgets.Add(EWidgetMode::Battle, CreateWidget<UBSBaseWidget>(GetWorld(), BattleWidgetClass));
	Widgets.Add(EWidgetMode::Inventory, CreateWidget<UBSBaseWidget>(GetWorld(), InventoryWidgetClass));
	Widgets.Add(EWidgetMode::Pause, CreateWidget<UBSBaseWidget>(GetWorld(), PauseWidgetClass));

	for (auto WidgetPair : Widgets)
	{
		UBSBaseWidget* WidgetIndex = WidgetPair.Value;
		if (!WidgetIndex) continue;

		WidgetIndex->AddToViewport();
		WidgetIndex->SetVisibility(ESlateVisibility::Hidden);
	}

	CurrentWidget = Widgets[EWidgetMode::Battle];
	CurrentWidget->SetVisibility(ESlateVisibility::Visible);

}

void ABSGameHUD::ChangeWidget(EWidgetMode NewWidget)
{
	if (!Widgets.Contains(NewWidget)) return;

	if (Widgets[NewWidget] == CurrentWidget && NewWidget != EWidgetMode::Battle)
	{
		ChangeWidget(EWidgetMode::Battle);
	}
	else if (Widgets[NewWidget] != CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
		CurrentWidget = Widgets[NewWidget];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);

		CurrentWidget->BeginFunc();
	}

}
