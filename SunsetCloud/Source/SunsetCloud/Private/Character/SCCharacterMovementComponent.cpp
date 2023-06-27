// This project, SunsetCloud, is the intellectual property of its author.


#include "Character/SCCharacterMovementComponent.h"
#include "GameFramework/Character.h"

#pragma region SavedMove
USCCharacterMovementComponent::FSavedMove_SCCharacter::FSavedMove_SCCharacter()
{
	Saved_bWantsToSprint = 0;
}

// 현재 SavedMove와 새롭게 만들어진 SavedMove를 결합할 수 있는지 여부를 리턴 하는 함수.
bool USCCharacterMovementComponent::FSavedMove_SCCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	FSavedMove_SCCharacter* NewSCCharacterMove = static_cast<FSavedMove_SCCharacter*>(NewMove.Get());
	
	// 현재 움직임과 새로운 움직임의 상태 변수 값이 동일한 경우에는 두 움직임을 하나로 결합해 대역폭을 절약.
	// 상태 변수 값이 동일하지 않은 경우 두 움직임을 결합할 수 없으므로 false를 리턴.
	if (Saved_bWantsToSprint != NewSCCharacterMove->Saved_bWantsToSprint)
	{
		return false;
	}

	// 기본 SavedMove 클래스에는 다른 움직임 관련 상태 변수들이 존재하기 때문에 Super 함수를 호출해서 기본 변수들에 대해서 처리해줌.
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta); 
}

// SavedMove를 빈 상태로 초기화 하는 함수.
void USCCharacterMovementComponent::FSavedMove_SCCharacter::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
}

// 움직임과 관련된 상태가 저장된 비트 플래그를 리턴하는 함수.
uint8 USCCharacterMovementComponent::FSavedMove_SCCharacter::GetCompressedFlags() const
{
	// 단발성 상태가 아닌 매 프레임마다 업데이트 되어야 하는 움직임 관련 상태 데이터를 비트 연산자를 통해 플래그에 추가해줌.
	uint8 Result = Super::GetCompressedFlags();

	if (Saved_bWantsToSprint) Result |= FLAG_Custom_0;

	return Result;
}

// SavedMove 클래스 데이터를 채워주는 함수.
void USCCharacterMovementComponent::FSavedMove_SCCharacter::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	USCCharacterMovementComponent* CharacterMovement = Cast<USCCharacterMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}

// SavedMove 클래스 데이터를 이용, CharacterMovementComponent의 현재 움직임 상태 데이터를 채워줌.(SetMoveFor 함수의 반대.)
void USCCharacterMovementComponent::FSavedMove_SCCharacter::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	USCCharacterMovementComponent* CharacterMovement = Cast<USCCharacterMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
}
#pragma endregion

#pragma region FNetworkPredictionData
USCCharacterMovementComponent::FNetworkPredictionData_Client_SCCharacter::FNetworkPredictionData_Client_SCCharacter(const UCharacterMovementComponent& ClientMovement)
	:Super(ClientMovement)
{
}

FSavedMovePtr USCCharacterMovementComponent::FNetworkPredictionData_Client_SCCharacter::AllocateNewMove()
{
	// 우리가 만든 SavedMove 클래스 인스턴스를 리턴해줌.
	return FSavedMovePtr(new FSavedMove_SCCharacter());
}

FNetworkPredictionData_Client* USCCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if (ClientPredictionData == nullptr)
	{
		USCCharacterMovementComponent* MutableThis = const_cast<USCCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_SCCharacter(*this); // 우리가 만든 커스텀 PredictionData 클래스 인스턴스를 만들어줌.
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}
	return ClientPredictionData;
}

// SavedMove 클래스의 움직임 관련 상태 플래그를 통해 캐릭터의 움직임 상태를 업데이트하는 함수.
void USCCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

// 매 프레임 마다 움직임 업데이트의 마지막에 호출되는 함수.
void USCCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	// 달리는 상태인 경우, 우리가 원하는 이동 속력으로 설정해줌.
	if (MovementMode == MOVE_Walking)
	{
		if (Safe_bWantsToSprint)
		{
			MaxWalkSpeed = Sprint_MaxWalkSpeed;
		}
		else
		{
			MaxWalkSpeed = Walk_MaxWalkSpeed;
		}
	}
}

#pragma endregion

#pragma region CMC

USCCharacterMovementComponent::USCCharacterMovementComponent()
{
	NavAgentProps.bCanCrouch = true;
}
#pragma endregion

#pragma region Sprint
void USCCharacterMovementComponent::EnterSprint()
{
	Safe_bWantsToSprint = true;
}

void USCCharacterMovementComponent::ExitSprint()
{
	Safe_bWantsToSprint = false;
}
#pragma endregion

#pragma region Crouch
void USCCharacterMovementComponent::ToggleCrouch()
{
	bWantsToCrouch = ~bWantsToCrouch;
}
#pragma endregion