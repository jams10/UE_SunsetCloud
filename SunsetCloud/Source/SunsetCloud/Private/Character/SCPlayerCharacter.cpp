// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCPlayerCharacter.h"
#include "Character/SCCharacterMovementComponent.h"

ASCPlayerCharacter::ASCPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:ASCCharacterBase(ObjectInitializer.SetDefaultSubobjectClass<USCCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// 캐릭터 무브먼트 컴포넌트를 우리가 만들어준 커스텀 CMC 타입으로 캐스팅하고, 나중에 사용하기 위해 참조를 따로 저장해줌.
	SCCharacterMovementComponent = Cast<USCCharacterMovementComponent>(GetCharacterMovement());

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 회전하도록 함.

	// 컨트롤러 회전에 따라 캐릭터가 회전하지 않도록 함.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
