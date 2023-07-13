// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SCUserWidget.h"

void USCUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	// 위젯이 참조할 위젯 컨트롤러를 세팅하면, WidgetControllerSet() 함수를 호출, 
	// 위젯 컨트롤러를 통해 AttributeSet, PlayerState 등에서 데이터를 받아와 위젯이 표시할 초기 값 세팅 및 이벤트 바인딩.
	WidgetControllerSet();
}

