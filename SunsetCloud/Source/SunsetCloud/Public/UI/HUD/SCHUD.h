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
	TSubclassOf<USCUserWidget> OverlayWidgetClass;						// �������� ���� Ŭ����. Overlay ����.

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass; // Overlay ������ �����͸� �޾ƿ� ���� ��Ʈ�ѷ� Ŭ����.

	UPROPERTY()
	TObjectPtr<USCUserWidget> OverlayWidget;							// ������ Overlay ���� ĳ��.
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;		// ������ OverlayWidgetController ĳ��.
};
