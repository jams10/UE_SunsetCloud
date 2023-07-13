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
	// 캐릭터 무브먼트 컴포넌트를 우리가 만들어준 커스텀 CMC 타입으로 캐스팅하고, 나중에 사용하기 위해 참조를 따로 저장해줌.
	SCCharacterMovementComponent = Cast<USCCharacterMovementComponent>(GetCharacterMovement());

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 회전하도록 함.

	// 컨트롤러 회전에 따라 캐릭터가 회전하지 않도록 함.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ASCPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 서버에서 Init Ability Actor Info.
	InitAbilityActorInfo();
}

void ASCPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 클라이언트에서 Init Ability Actor Info.
	InitAbilityActorInfo();
}

void ASCPlayerCharacter::InitAbilityActorInfo()
{
	ASCPlayerState* SCPlayerState = GetPlayerState<ASCPlayerState>();
	check(SCPlayerState);
	SCPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SCPlayerState, this);
	AbilitySystemComponent = SCPlayerState->GetAbilitySystemComponent();
	AttributeSet = SCPlayerState->GetAttributeSet();

	// 이 함수에서는 바로 위에서 PlayerState를 설정해 줌은 물론이고, 
	// 이 함수를 각각 서버, 클라이언트에서 호출해 줄 때 플레이어 컨트롤러가 설정 되어 있음이 보장되기 때문에 InitOverlay에서 필요한
	// APlayerController, APlayerState, UAbilitySystemComponent, UAttributeSet이 모두 유효한 상태임.
	// HUD는 항상 플레이어 컨트롤러를 통해 접근 가능함.
	if (ASCPlayerController* SCPlayerController = Cast<ASCPlayerController>(GetController()))
	{
		// 멀티 플레이어에서 클라이언트의 경우에는 자신의 로컬 플레이어 컨트롤러는 유효하지만 다른 클라이언트의 컨트롤러는 유효하지 않음.
		if (ASCHUD* SCHUD = Cast<ASCHUD>(SCPlayerController->GetHUD()))
		{
			SCHUD->InitOverlay(SCPlayerController, SCPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
