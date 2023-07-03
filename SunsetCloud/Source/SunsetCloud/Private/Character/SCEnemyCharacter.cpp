// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCEnemyCharacter.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/SCAttributeSet.h"

ASCEnemyCharacter::ASCEnemyCharacter()
{
	// 몬스터의 경우 바로 Enemy 클래스에 ASC와 AS를 붙여줌.
	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<USCAttributeSet>("AttributeSet");

	// Replication Mode를 Minimal로 설정.
	// GameplayEffect는 복제 되지 않음. 서버에서만 처리.
	// Cue와 Tag는 모든 클라이언트에 복제.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}
