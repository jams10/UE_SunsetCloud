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
	// 반드시 GameplayEffect를 통해 attribute 값을 변경해야 함. 여기서 작성한 코드는 학습을 위한 실험용 코드!

	// 오버랩된 액터가 AbilitySystemInterface를 상속 받고 있는지 체크함.
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		// 해당 액터의 ASC에 접근, ASC와 연결되어 있는 AttributeSet을 얻어옴.
		const USCAttributeSet* SCAttributeSet =
			Cast<USCAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(USCAttributeSet::StaticClass()));

		USCAttributeSet* MutableSCAttributeSet = const_cast<USCAttributeSet*>(SCAttributeSet);
		MutableSCAttributeSet->SetHealth(SCAttributeSet->GetHealth() + 25.f); // 직접 Attribute의 값을 바꾸고 있음.
		Destroy();
	}
}

void ASCEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


