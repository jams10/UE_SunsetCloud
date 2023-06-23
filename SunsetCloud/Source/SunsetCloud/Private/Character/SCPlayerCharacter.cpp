// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCPlayerCharacter.h"
#include "Character/SCCharacterMovementComponent.h"

ASCPlayerCharacter::ASCPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:ASCCharacterBase(ObjectInitializer.SetDefaultSubobjectClass<USCCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// 캐릭터 무브먼트 컴포넌트를 우리가 만들어준 커스텀 CMC 타입으로 캐스팅하고, 나중에 사용하기 위해 참조를 따로 저장해줌.
	SCCharacterMovementComponent = Cast<USCCharacterMovementComponent>(GetCharacterMovement());
}
