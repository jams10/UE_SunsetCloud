// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "SCCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 *	��� ĳ���� Ŭ�������� �⺻ Ŭ����.
 */
UCLASS(Abstract)  // �ܼ� Base Ŭ���� ���Ҹ� ��. ���� ��� ���� Ŭ������ �ν��Ͻ��� ����� ������ ���� �� �ֵ��� ��.
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
