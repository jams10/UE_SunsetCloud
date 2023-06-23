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

	// SavedMove : 한 프레임 내에서의 움직임을 만들어내기 위해 필요한 모든 상태 데이터를 캡쳐한 스냅샷.
	// - 네트워크 상에서 서버와 클라이언트 캐릭터의 동기화된 움직임을 위해 클라이언트쪽에서 SavedMove 클래스 정보를 채워 서버로 보냄.
    // - 서버에서는 SavedMove 클래스에 저장된 정보를 통해 클라이언트의 움직임을 시뮬레이션하고, 서버 캐릭터의 움직임과 비교해 server-correction을 수행함.
	class FSavedMove_SCCharacter : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;

		uint8 Saved_bWantsToSprint : 1; // 입력을 통해 캐릭터가 달리고자 하는지 여부.

	public:
		FSavedMove_SCCharacter();

		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	// 직접 만든 커스텀 SavedMove 클래스를 사용할 것임을 알려주는 역할을 하는 클래스.
	// Allocate 함수를 통해 우리가 원하는 커스텀 SavedMove 클래스를 새 Move로 할당해줌.
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
