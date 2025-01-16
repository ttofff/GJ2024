// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GJ2024/GJ2024GameModeBase.h"
#include "GJ2024GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GJ2024_API UGJ2024GameInstance : public UGameInstance
{
	GENERATED_BODY()

	UGJ2024GameInstance();

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BGM")
	UAudioComponent* MainBgmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BGM")
	USoundBase* MainBGM;

public:
	UFUNCTION(BlueprintCallable)
	void PlayMainBGM();

	UFUNCTION(BlueprintCallable)
	void StopMainBGM();
};
