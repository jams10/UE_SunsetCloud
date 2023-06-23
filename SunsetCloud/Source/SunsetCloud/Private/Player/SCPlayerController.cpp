// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASCPlayerController::ASCPlayerController()
{
	bReplicates = true;
}

void ASCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MappingContext); // check 매크로는 인자로 넘겨준 식이 유효하지 않은 경우 실행을 중단 시킴.

	// UEnhancedInputLocalPlayerSubsystem을 이용해 입력에 사용할 InputMappingContext를 추가함.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext, 0); 
}

void ASCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// CastChecked는 포인터 캐스팅과 동시에 check 매크로를 실행하는 것과 동일함. 
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCPlayerController::Move);
}

void ASCPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Move 함수가 매 프레임마다 호출될 수 있기 때문에 아직 ControlledPawn이 nullptr일 수 있어 체크해줌.
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}