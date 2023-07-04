// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SCCharacterBase.h"
#include "SCEnemyCharacter.generated.h"

/**
 *	적 AI 캐릭터 클래스.
 */
UCLASS()
class SUNSETCLOUD_API ASCEnemyCharacter : public ASCCharacterBase
{
	GENERATED_BODY()
	
public:
	ASCEnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
