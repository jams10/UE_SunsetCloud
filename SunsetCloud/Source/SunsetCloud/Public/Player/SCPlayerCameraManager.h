// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "SCPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class SUNSETCLOUD_API ASCPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
private:

	UPROPERTY(EditDefaultsOnly) 
	float CrouchBlendDuration = .5f;
	
	float CrouchBlendTime;
public:
	ASCPlayerCameraManager();

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
