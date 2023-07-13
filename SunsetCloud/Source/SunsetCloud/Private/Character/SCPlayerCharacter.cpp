// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Character/SCCharacterMovementComponent.h"
#include "Player/SCPlayerController.h"
#include "Player/SCPlayerState.h"
#include "UI/HUD/SCHUD.h"

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

	// �� �Լ������� �ٷ� ������ PlayerState�� ������ ���� �����̰�, 
	// �� �Լ��� ���� ����, Ŭ���̾�Ʈ���� ȣ���� �� �� �÷��̾� ��Ʈ�ѷ��� ���� �Ǿ� ������ ����Ǳ� ������ InitOverlay���� �ʿ���
	// APlayerController, APlayerState, UAbilitySystemComponent, UAttributeSet�� ��� ��ȿ�� ������.
	// HUD�� �׻� �÷��̾� ��Ʈ�ѷ��� ���� ���� ������.
	if (ASCPlayerController* SCPlayerController = Cast<ASCPlayerController>(GetController()))
	{
		// ��Ƽ �÷��̾�� Ŭ���̾�Ʈ�� ��쿡�� �ڽ��� ���� �÷��̾� ��Ʈ�ѷ��� ��ȿ������ �ٸ� Ŭ���̾�Ʈ�� ��Ʈ�ѷ��� ��ȿ���� ����.
		if (ASCHUD* SCHUD = Cast<ASCHUD>(SCPlayerController->GetHUD()))
		{
			SCHUD->InitOverlay(SCPlayerController, SCPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
