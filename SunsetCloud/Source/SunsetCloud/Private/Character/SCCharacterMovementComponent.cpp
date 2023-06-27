// This project, SunsetCloud, is the intellectual property of its author.


#include "Character/SCCharacterMovementComponent.h"
#include "GameFramework/Character.h"

#pragma region SavedMove
USCCharacterMovementComponent::FSavedMove_SCCharacter::FSavedMove_SCCharacter()
{
	Saved_bWantsToSprint = 0;
}

// ���� SavedMove�� ���Ӱ� ������� SavedMove�� ������ �� �ִ��� ���θ� ���� �ϴ� �Լ�.
bool USCCharacterMovementComponent::FSavedMove_SCCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	FSavedMove_SCCharacter* NewSCCharacterMove = static_cast<FSavedMove_SCCharacter*>(NewMove.Get());
	
	// ���� �����Ӱ� ���ο� �������� ���� ���� ���� ������ ��쿡�� �� �������� �ϳ��� ������ �뿪���� ����.
	// ���� ���� ���� �������� ���� ��� �� �������� ������ �� �����Ƿ� false�� ����.
	if (Saved_bWantsToSprint != NewSCCharacterMove->Saved_bWantsToSprint)
	{
		return false;
	}

	// �⺻ SavedMove Ŭ�������� �ٸ� ������ ���� ���� �������� �����ϱ� ������ Super �Լ��� ȣ���ؼ� �⺻ �����鿡 ���ؼ� ó������.
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta); 
}

// SavedMove�� �� ���·� �ʱ�ȭ �ϴ� �Լ�.
void USCCharacterMovementComponent::FSavedMove_SCCharacter::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
}

// �����Ӱ� ���õ� ���°� ����� ��Ʈ �÷��׸� �����ϴ� �Լ�.
uint8 USCCharacterMovementComponent::FSavedMove_SCCharacter::GetCompressedFlags() const
{
	// �ܹ߼� ���°� �ƴ� �� �����Ӹ��� ������Ʈ �Ǿ�� �ϴ� ������ ���� ���� �����͸� ��Ʈ �����ڸ� ���� �÷��׿� �߰�����.
	uint8 Result = Super::GetCompressedFlags();

	if (Saved_bWantsToSprint) Result |= FLAG_Custom_0;

	return Result;
}

// SavedMove Ŭ���� �����͸� ä���ִ� �Լ�.
void USCCharacterMovementComponent::FSavedMove_SCCharacter::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	USCCharacterMovementComponent* CharacterMovement = Cast<USCCharacterMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}

// SavedMove Ŭ���� �����͸� �̿�, CharacterMovementComponent�� ���� ������ ���� �����͸� ä����.(SetMoveFor �Լ��� �ݴ�.)
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
	// �츮�� ���� SavedMove Ŭ���� �ν��Ͻ��� ��������.
	return FSavedMovePtr(new FSavedMove_SCCharacter());
}

FNetworkPredictionData_Client* USCCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if (ClientPredictionData == nullptr)
	{
		USCCharacterMovementComponent* MutableThis = const_cast<USCCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_SCCharacter(*this); // �츮�� ���� Ŀ���� PredictionData Ŭ���� �ν��Ͻ��� �������.
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}
	return ClientPredictionData;
}

// SavedMove Ŭ������ ������ ���� ���� �÷��׸� ���� ĳ������ ������ ���¸� ������Ʈ�ϴ� �Լ�.
void USCCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

// �� ������ ���� ������ ������Ʈ�� �������� ȣ��Ǵ� �Լ�.
void USCCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	// �޸��� ������ ���, �츮�� ���ϴ� �̵� �ӷ����� ��������.
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