// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SCUserWidget.h"

void USCUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	// ������ ������ ���� ��Ʈ�ѷ��� �����ϸ�, WidgetControllerSet() �Լ��� ȣ��, 
	// ���� ��Ʈ�ѷ��� ���� AttributeSet, PlayerState ��� �����͸� �޾ƿ� ������ ǥ���� �ʱ� �� ���� �� �̺�Ʈ ���ε�.
	WidgetControllerSet();
}

