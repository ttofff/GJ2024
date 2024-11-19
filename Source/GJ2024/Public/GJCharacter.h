// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GJCharacter.generated.h"

//角色状态
UENUM(BlueprintType)
enum class ECharacterStates : uint8
{
	E_Common UMETA(DisplayName = "Common"),//普通状态
	E_Jump UMETA(DisplayName = "Jump"),//跳跃状态
	E_Attack UMETA(DisplayName = "Attack"),//攻击状态
	E_Build UMETA(DisplayName = "Build"),//建造状态
	E_Interaction UMETA(DisplayName = "Interaction")//交互状态
};

//背包物品信息
USTRUCT(BlueprintType)
struct FBackpackInformation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BackpackWeight = 100.f;//背包大小

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 WoodCnt = 0;//木材数量

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MineralCnt = 0;//矿物数量

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 FoodCnt = 0;//食物数量
};

UCLASS()
class GJ2024_API AGJCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* PlayerCameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackBox;

public:
	//限制相机旋转角度
	float ClampCameraRotation = 0.f;

	//限制相机旋转速度
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "PlayerCamera")
	float RotationRate;

	//原始速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PlayerSpeed")
	float OriginalSpeed;

	//疾跑速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PlayerSpeed")
	float AcceleratedSpeed;

	//弹簧臂每次加减长度
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "PlayerCamera")
	float ArmLengthValue;

	//角色状态
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PlayerStates")
	ECharacterStates CharacterStates;

	//背包信息
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PlayerBackpack")
	FBackpackInformation BackpackInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Look(float value);

	void Turn(float value);

	void MoveForward(float value);

	void MoveRight(float value);

	void Accelerate();

	void Decelerate();
	
	void Jump();
	
	void StopJumping();

	void ModifyArmLength(float value);

	void Attack();

	void OpenBackpack();

public:
	// Sets default values for this character's properties
	AGJCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
