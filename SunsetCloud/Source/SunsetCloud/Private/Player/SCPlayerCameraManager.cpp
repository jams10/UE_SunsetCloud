// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerCameraManager.h"
#include "Character/SCPlayerCharacter.h"
#include "Character/SCCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ASCPlayerCameraManager::ASCPlayerCameraManager()
{
}

void ASCPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	// 캐릭터 액터에 대한 참조를 얻어옴.
	if (ASCPlayerCharacter* SCCharacter = Cast<ASCPlayerCharacter>(GetOwningPlayerController()->GetPawn()))
	{
		// CMC에 대한 참조를 얻어옴.
		USCCharacterMovementComponent* CMC = SCCharacter->GetZippyCharacterMovement();

		// Target Offset = crouch half height - defualt half height
		// 캡슐의 half height는 crouch 여부에 따라 달라질 수 있기 때문에 곧바로 CMC에서 캡슐 높이를 얻어오면 안됨. 따라서 기본 ACharacter 클래스의 높이를 얻어옴. 
		FVector TargetCrouchOffset = FVector(0, 0, CMC->GetCrouchedHalfHeight() - SCCharacter->GetClass()->GetDefaultObject<ACharacter>()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

		// 실제 적용될 Offset 값.
		// TargetCrouchOffset 값으로 BlendTime을 Alpha 값으로 하여 선형 보간.
		FVector Offset = FMath::Lerp(FVector::ZeroVector, TargetCrouchOffset, FMath::Clamp(CrouchBlendTime / CrouchBlendDuration, 0.f, 1.f));

		if (CMC->IsCrouching())
		{
			// Crouch 상태로 들어가면, BlendTime은 0에서 서서히 커지면서 CrouchBlendDuration 값으로 변경됨.
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime + DeltaTime, 0.f, CrouchBlendDuration);
			// Crouch 상태로 들어가는 경우, 카메라가 바로 아래 쪽으로 스내핑 되는 것을 막기 위해 스내핑 되는 양 만큼 반대로 이동 시켜줌. (negate)
			Offset -= TargetCrouchOffset;
		}
		else
		{
			// Crouch 상태가 아닌 경우, BlendTime은 CrouchBlendDuration 값에서 0으로 서서히 작아짐.
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime - DeltaTime, 0.f, CrouchBlendDuration);
		}

		// 점프 동안에는 카메라 위치가 변경되지 않기 때문에 땅 위에 있는 경우에만 오프셋을 더해 카메라의 위치를 변경해줌.
		if (CMC->IsMovingOnGround())
		{
			// 오프셋을 적용해줌.
			OutVT.POV.Location += Offset;
		}
	}
}
