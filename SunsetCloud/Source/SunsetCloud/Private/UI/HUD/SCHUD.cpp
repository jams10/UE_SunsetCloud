// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/SCHUD.h"
#include "UI/Widget/SCUserWidget.h"

void ASCHUD::BeginPlay()
{
	Super::BeginPlay();

	// Overlay ���� ������ ����Ʈ�� �߰�.
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
