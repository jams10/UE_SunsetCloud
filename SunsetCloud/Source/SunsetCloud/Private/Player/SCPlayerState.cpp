// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerState.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/SCAttributeSet.h"

ASCPlayerState::ASCPlayerState()
{
	// NetUpdateFrequency : ������ �󸶳� ���� Ŭ���̾�Ʈ�� ������Ʈ �ϴ��� ����.
	// ASC�� AttributeSet�� PlayerState�� �߰��ϴ� ���, �� ���� ���� ������ �־�� ��.
	NetUpdateFrequency = 100.f; 

	// �÷��̾� ĳ������ ��� PlayerState�� ASC�� AttributeSet�� �߰�����. �������� ������� �ʰ� �����ǵ��� ��.
	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<USCAttributeSet>("AttributeSet");

	// Replication Mode�� Mixed�� ����.
	// GameplayEffect : Owning Client�� ����.
	// GameplayCue, Tag : ��� Ŭ���̾�Ʈ�� ����.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ASCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
