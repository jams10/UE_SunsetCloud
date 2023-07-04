// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SCAttributeSet.h"
#include "Net/UnrealNetwork.h"

USCAttributeSet::USCAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(100.f);
	InitMaxMana(100.f);
	InitStamina(100.f);
	InitMaxStamina(100.f);
}

void USCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Attribute 값들이 복제 되도록 등록. REPNOTIFY_Always는 해당 변수의 값의 변경 여부 상관 없이 항상 replicate.
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void USCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// RepNotify 함수 바디의 경우 언리얼에서 제공하는 매크로를 통해 정의할 수 있음.
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Health, OldHealth);
}

void USCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxHealth, OldMaxHealth);
}

void USCAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Mana, OldMana);
}

void USCAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxMana, OldMaxMana);
}

void USCAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Stamina, OldStamina);
}

void USCAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxStamina, OldMaxStamina);
}
