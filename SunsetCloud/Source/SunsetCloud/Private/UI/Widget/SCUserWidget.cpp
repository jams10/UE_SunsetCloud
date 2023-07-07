// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SCUserWidget.h"

void USCUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

