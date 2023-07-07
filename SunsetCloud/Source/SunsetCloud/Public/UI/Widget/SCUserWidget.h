// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SCUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUNSETCLOUD_API USCUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController; // 위젯이 참조하는 위젯 컨트롤러. 

protected:

	// 위젯 컨트롤러가 세팅 될 때 이 함수를 호출해서 위젯의 초기 값들을 설정 해 줌.
	// 초기화 로직을 블루프린트에서 구현하기 위해 BlueprintImplementableEvent로 만들어줌.
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
