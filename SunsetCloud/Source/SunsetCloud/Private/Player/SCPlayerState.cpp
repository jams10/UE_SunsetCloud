// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerState.h"

ASCPlayerState::ASCPlayerState()
{
	// NetUpdateFrequency : 서버가 얼마나 자주 클라이언트를 업데이트 하는지 결정.
	// ASC와 AttributeSet을 PlayerState에 추가하는 경우, 이 값을 높게 설정해 주어야 함.
	NetUpdateFrequency = 100.f; 
}
