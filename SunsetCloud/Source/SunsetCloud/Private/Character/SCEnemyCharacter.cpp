// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCEnemyCharacter.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/SCAttributeSet.h"

ASCEnemyCharacter::ASCEnemyCharacter()
{
	// ������ ��� �ٷ� Enemy Ŭ������ ASC�� AS�� �ٿ���.
	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<USCAttributeSet>("AttributeSet");

	// Replication Mode�� Minimal�� ����.
	// GameplayEffect�� ���� ���� ����. ���������� ó��.
	// Cue�� Tag�� ��� Ŭ���̾�Ʈ�� ����.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}
