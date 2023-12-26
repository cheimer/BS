// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSMenuHUD.h"
#include "UI/BSBaseWidget.h"

void ABSMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	Widgets.Add(EMenuWidgetMode::Main, CreateWidget<UBSBaseWidget>(GetWorld(), MenuWidgetClass));
	Widgets.Add(EMenuWidgetMode::Custom, CreateWidget<UBSBaseWidget>(GetWorld(), CustomWidgetClass));

	for (auto WidgetPair : Widgets)
	{
		UBSBaseWidget* WidgetIndex = WidgetPair.Value;
		if (!WidgetIndex) continue;

		WidgetIndex->AddToViewport();
		WidgetIndex->SetVisibility(ESlateVisibility::Hidden);
	}

	CurrentWidget = Widgets[EMenuWidgetMode::Main];
	CurrentWidget->SetVisibility(ESlateVisibility::Visible);
}

void ABSMenuHUD::ChangeWidget(EMenuWidgetMode NewWidget)
{
	if (!Widgets.Contains(NewWidget)) return;
	if (Widgets[NewWidget] == CurrentWidget) return;

	else if (Widgets[NewWidget] != CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
		CurrentWidget = Widgets[NewWidget];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);

		CurrentWidget->BeginFunc();
	}


}
