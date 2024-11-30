// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "NPC_Character.generated.h"

UCLASS()
class GJ2024_API ANPC_Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	USphereComponent* InteractionCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	USphereComponent* TipCollision;

	//消失烟雾的粒子系统
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "NiagaraComponent", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* DisappearNiagaraComponent;

public:
	//给任务时的文本
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	TArray<FText> InteractionTexts;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	FVector CampLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	FRotator CampRotation;

	//是否点击
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	bool bIsClick = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	int32 IndexText = 0;

	//任务内容
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	FText TaskContent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	bool bIsCommon = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "NPC", meta=(AllowPrivateAccess = "true"))
	TArray<FText> CommonTexts;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	ANPC_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
