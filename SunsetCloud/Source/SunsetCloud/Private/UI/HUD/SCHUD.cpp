// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/SCHUD.h"
#include "UI/Widget/SCUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void ASCHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// checkf의 경우 상태를 체크하고 formatted string을 출력함.
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class 블루프린트 클래스가 등록되지 않았음."));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class 블루프린트 클래스가 등록되지 않았음."));

	// Overlay 위젯 생성.
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<USCUserWidget>(Widget);

	// Overlay 위젯이 참조할 위젯 컨트롤러 설정.
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues(); // 위젯에 위젯 컨트롤러를 할당하고, 초기 값을 Broadcast.
	
	Widget->AddToViewport();
}

UOverlayWidgetController* ASCHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	// OverlayWidgetController가 없으면 만들어서 리턴함.
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}


