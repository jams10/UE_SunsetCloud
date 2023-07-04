// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SCEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "Components/SphereComponent.h"

ASCEffectActor::ASCEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ASCEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASCEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASCEffectActor::EndOverlap);
}

void ASCEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OhterBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ݵ�� GameplayEffect�� ���� attribute ���� �����ؾ� ��. ���⼭ �ۼ��� �ڵ�� �н��� ���� ����� �ڵ�!

	// �������� ���Ͱ� AbilitySystemInterface�� ��� �ް� �ִ��� üũ��.
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		// �ش� ������ ASC�� ����, ASC�� ����Ǿ� �ִ� AttributeSet�� ����.
		const USCAttributeSet* SCAttributeSet =
			Cast<USCAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(USCAttributeSet::StaticClass()));

		USCAttributeSet* MutableSCAttributeSet = const_cast<USCAttributeSet*>(SCAttributeSet);
		MutableSCAttributeSet->SetHealth(SCAttributeSet->GetHealth() + 25.f); // ���� Attribute�� ���� �ٲٰ� ����.
		Destroy();
	}
}

void ASCEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


