// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SCCharacterBase.h"
#include "SCPlayerCharacter.generated.h"

class USCCharacterMovementComponent;

/**
 *	Player 캐릭터 클래스.
 */
UCLASS()
class SUNSETCLOUD_API ASCPlayerCharacter : public ASCCharacterBase
{
	GENERATED_BODY()
	
public:
	ASCPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	FORCEINLINE USCCharacterMovementComponent* GetZippyCharacterMovement() const { return SCCharacterMovementComponent; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement) 
	USCCharacterMovementComponent* SCCharacterMovementComponent;
};
