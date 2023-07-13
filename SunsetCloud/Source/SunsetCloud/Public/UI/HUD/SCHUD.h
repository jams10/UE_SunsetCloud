// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "SCHUD.generated.h"

class USCUserWidget;
class UOverlayWidgetController;

UCLASS()
class SUNSETCLOUD_API ASCHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

protected:

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<USCUserWidget> OverlayWidgetClass;						// 생성해줄 위젯 클래스. Overlay 위젯.

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass; // Overlay 위젯이 데이터를 받아올 위젯 컨트롤러 클래스.

	UPROPERTY()
	TObjectPtr<USCUserWidget> OverlayWidget;							// 생성한 Overlay 위젯 캐싱.
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;		// 생성한 OverlayWidgetController 캐싱.
};
