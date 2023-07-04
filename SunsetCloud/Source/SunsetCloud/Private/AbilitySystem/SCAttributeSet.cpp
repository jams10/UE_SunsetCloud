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

	// Attribute ������ ���� �ǵ��� ���. REPNOTIFY_Always�� �ش� ������ ���� ���� ���� ��� ���� �׻� replicate.
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void USCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// RepNotify �Լ� �ٵ��� ��� �𸮾󿡼� �����ϴ� ��ũ�θ� ���� ������ �� ����.
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
