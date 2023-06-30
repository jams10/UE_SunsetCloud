// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "SCCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 *	모든 캐릭터 클래스들의 기본 클래스.
 */
UCLASS(Abstract)  // 단순 Base 클래스 역할만 함. 오직 상속 받은 클래스만 인스턴스를 만들어 레벨에 놓을 수 있도록 함.
class SUNSETCLOUD_API ASCCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASCCharacterBase();
	ASCCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	TObjectPtr<UAttributeSet> AttributeSet;

};
