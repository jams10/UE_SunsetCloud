// This project, SunsetCloud, is the intellectual property of its author.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SCCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUNSETCLOUD_API USCCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	// SavedMove : �� ������ �������� �������� ������ ���� �ʿ��� ��� ���� �����͸� ĸ���� ������.
	// - ��Ʈ��ũ �󿡼� ������ Ŭ���̾�Ʈ ĳ������ ����ȭ�� �������� ���� Ŭ���̾�Ʈ�ʿ��� SavedMove Ŭ���� ������ ä�� ������ ����.
    // - ���������� SavedMove Ŭ������ ����� ������ ���� Ŭ���̾�Ʈ�� �������� �ùķ��̼��ϰ�, ���� ĳ������ �����Ӱ� ���� server-correction�� ������.
	class FSavedMove_SCCharacter : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;

		uint8 Saved_bWantsToSprint : 1; // �Է��� ���� ĳ���Ͱ� �޸����� �ϴ��� ����.

	public:
		FSavedMove_SCCharacter();

		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	// ���� ���� Ŀ���� SavedMove Ŭ������ ����� ������ �˷��ִ� ������ �ϴ� Ŭ����.
	// Allocate �Լ��� ���� �츮�� ���ϴ� Ŀ���� SavedMove Ŭ������ �� Move�� �Ҵ�����.
	class FNetworkPredictionData_Client_SCCharacter : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_SCCharacter(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};

private:

	UPROPERTY(EditDefaultsOnly)
	float Sprint_MaxWalkSpeed;
	UPROPERTY(EditDefaultsOnly)
	float Walk_MaxWalkSpeed;

	bool Safe_bWantsToSprint;

public:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

public:
	USCCharacterMovementComponent();

	UFUNCTION(BlueprintCallable)
	void EnterSprint();
	UFUNCTION(BlueprintCallable)
	void ExitSprint();
};
