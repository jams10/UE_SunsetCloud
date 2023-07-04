// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SCCharacterBase.h"
#include "SCEnemyCharacter.generated.h"

/**
 *	�� AI ĳ���� Ŭ����.
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
