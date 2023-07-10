// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/SCHUD.h"
#include "UI/Widget/SCUserWidget.h"

void ASCHUD::BeginPlay()
{
	Super::BeginPlay();

	// Overlay 위젯 생성후 뷰포트에 추가.
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
