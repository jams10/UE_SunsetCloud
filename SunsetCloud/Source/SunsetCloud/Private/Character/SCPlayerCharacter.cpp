// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Character/SCCharacterMovementComponent.h"
#include "Player/SCPlayerState.h"

ASCPlayerCharacter::ASCPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:ASCCharacterBase(ObjectInitializer.SetDefaultSubobjectClass<USCCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// ĳ���� �����Ʈ ������Ʈ�� �츮�� ������� Ŀ���� CMC Ÿ������ ĳ�����ϰ�, ���߿� ����ϱ� ���� ������ ���� ��������.
	SCCharacterMovementComponent = Cast<USCCharacterMovementComponent>(GetCharacterMovement());

	GetCharacterMovement()->bOrientRotationToMovement = true; // �̵� �������� ȸ���ϵ��� ��.

	// ��Ʈ�ѷ� ȸ���� ���� ĳ���Ͱ� ȸ������ �ʵ��� ��.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ASCPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// �������� Init Ability Actor Info.
	InitAbilityActorInfo();
}

void ASCPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Ŭ���̾�Ʈ���� Init Ability Actor Info.
	InitAbilityActorInfo();
}

void ASCPlayerCharacter::InitAbilityActorInfo()
{
	ASCPlayerState* SCPlayerState = GetPlayerState<ASCPlayerState>();
	check(SCPlayerState);
	SCPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SCPlayerState, this);
	AbilitySystemComponent = SCPlayerState->GetAbilitySystemComponent();
	AttributeSet = SCPlayerState->GetAttributeSet();
}
