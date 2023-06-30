// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCPlayerCharacter.h"
#include "Character/SCCharacterMovementComponent.h"

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
