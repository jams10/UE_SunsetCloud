// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/SCAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// CastChecked는 말 그대로 체크된 상황에서 캐스팅 한다는 뜻. 우리가 이미 해당 타입이 템플릿 인자로 넘겨준 타입임을 알고 있을 때 사용.
	USCAttributeSet* SCAttributeSet = CastChecked<USCAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(SCAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(SCAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(SCAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(SCAttributeSet->GetMaxMana());
	OnStaminaChanged.Broadcast(SCAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(SCAttributeSet->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const USCAttributeSet* SCAttributeSet = CastChecked<USCAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate( // GameplayAttributeChangeDelegate는 멀티캐스트 델리게이트.
		SCAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCAttributeSet->GetStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxStaminaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	// FOnAttributeChangeData 구조체의 NewValue(바뀐 attribute 값)를 보내면서 broadcast.
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}
