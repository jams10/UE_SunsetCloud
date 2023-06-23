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
	check(MappingContext); // check ��ũ�δ� ���ڷ� �Ѱ��� ���� ��ȿ���� ���� ��� ������ �ߴ� ��Ŵ.

	// UEnhancedInputLocalPlayerSubsystem�� �̿��� �Է¿� ����� InputMappingContext�� �߰���.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext, 0); 
}

void ASCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// CastChecked�� ������ ĳ���ð� ���ÿ� check ��ũ�θ� �����ϴ� �Ͱ� ������. 
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

	// Move �Լ��� �� �����Ӹ��� ȣ��� �� �ֱ� ������ ���� ControlledPawn�� nullptr�� �� �־� üũ����.
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}