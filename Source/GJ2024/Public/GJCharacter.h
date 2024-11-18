// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GJCharacter.generated.h"

UCLASS()
class GJ2024_API AGJCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* PlayerCameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

public:
	//限制相机旋转角度
	float ClampCameraRotation = 0.f;

	//限制相机旋转速度
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Camera")
	float RotationRate;

	//原始速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Speed")
	float OriginalSpeed;

	//疾跑速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Speed")
	float AcceleratedSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Look(float value);

	void Turn(float value);

	void MoveForward(float value);

	void MoveRight(float value);

	void Accelerate();

	void Decelerate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Sets default values for this character's properties
	AGJCharacter();
	
};
