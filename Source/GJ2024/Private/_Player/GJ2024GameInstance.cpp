// Fill out your copyright notice in the Description page of Project Settings.


#include "_Player/GJ2024GameInstance.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UGJ2024GameInstance::UGJ2024GameInstance()
{
	
}

//播放背景音乐
void UGJ2024GameInstance::PlayMainBGM()
{
	MainBgmComponent = UGameplayStatics::SpawnSound2D(this,MainBGM);
	MainBgmComponent->Play();
}

//停止背景音乐
void UGJ2024GameInstance::StopMainBGM()
{
	MainBgmComponent->Stop();
}
