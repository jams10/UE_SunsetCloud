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

	// ĳ���� ���Ϳ� ���� ������ ����.
	if (ASCPlayerCharacter* SCCharacter = Cast<ASCPlayerCharacter>(GetOwningPlayerController()->GetPawn()))
	{
		// CMC�� ���� ������ ����.
		USCCharacterMovementComponent* CMC = SCCharacter->GetZippyCharacterMovement();

		// Target Offset = crouch half height - defualt half height
		// ĸ���� half height�� crouch ���ο� ���� �޶��� �� �ֱ� ������ ��ٷ� CMC���� ĸ�� ���̸� ������ �ȵ�. ���� �⺻ ACharacter Ŭ������ ���̸� ����. 
		FVector TargetCrouchOffset = FVector(0, 0, CMC->GetCrouchedHalfHeight() - SCCharacter->GetClass()->GetDefaultObject<ACharacter>()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

		// ���� ����� Offset ��.
		// TargetCrouchOffset ������ BlendTime�� Alpha ������ �Ͽ� ���� ����.
		FVector Offset = FMath::Lerp(FVector::ZeroVector, TargetCrouchOffset, FMath::Clamp(CrouchBlendTime / CrouchBlendDuration, 0.f, 1.f));

		if (CMC->IsCrouching())
		{
			// Crouch ���·� ����, BlendTime�� 0���� ������ Ŀ���鼭 CrouchBlendDuration ������ �����.
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime + DeltaTime, 0.f, CrouchBlendDuration);
			// Crouch ���·� ���� ���, ī�޶� �ٷ� �Ʒ� ������ ������ �Ǵ� ���� ���� ���� ������ �Ǵ� �� ��ŭ �ݴ�� �̵� ������. (negate)
			Offset -= TargetCrouchOffset;
		}
		else
		{
			// Crouch ���°� �ƴ� ���, BlendTime�� CrouchBlendDuration ������ 0���� ������ �۾���.
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime - DeltaTime, 0.f, CrouchBlendDuration);
		}

		// ���� ���ȿ��� ī�޶� ��ġ�� ������� �ʱ� ������ �� ���� �ִ� ��쿡�� �������� ���� ī�޶��� ��ġ�� ��������.
		if (CMC->IsMovingOnGround())
		{
			// �������� ��������.
			OutVT.POV.Location += Offset;
		}
	}
}
