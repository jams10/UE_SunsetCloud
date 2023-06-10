// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCCharacterBase.generated.h"

/**
 *	��� ĳ���� Ŭ�������� �⺻ Ŭ����.
 */
UCLASS()
class SUNSETCLOUD_API ASCCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASCCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
