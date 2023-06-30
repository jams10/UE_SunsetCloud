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
}
