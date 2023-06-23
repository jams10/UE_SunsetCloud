// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCCharacterBase.h"

ASCCharacterBase::ASCCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

ASCCharacterBase::ASCCharacterBase(const FObjectInitializer& ObjectInitializer)
	:ACharacter(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
