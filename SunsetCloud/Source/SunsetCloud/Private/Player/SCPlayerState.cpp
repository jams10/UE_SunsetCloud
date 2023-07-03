// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerState.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/SCAttributeSet.h"

ASCPlayerState::ASCPlayerState()
{
	// NetUpdateFrequency : 서버가 얼마나 자주 클라이언트를 업데이트 하는지 결정.
	// ASC와 AttributeSet을 PlayerState에 추가하는 경우, 이 값을 높게 설정해 주어야 함.
	NetUpdateFrequency = 100.f; 

	// 플레이어 캐릭터의 경우 PlayerState에 ASC와 AttributeSet을 추가해줌. 리스폰시 사라지지 않고 유지되도록 함.
	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<USCAttributeSet>("AttributeSet");

	// Replication Mode를 Mixed로 설정.
	// GameplayEffect : Owning Client에 복제.
	// GameplayCue, Tag : 모든 클라이언트에 복제.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ASCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
