// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCCharacterBase.generated.h"

/**
 *	모든 캐릭터 클래스들의 기본 클래스.
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
