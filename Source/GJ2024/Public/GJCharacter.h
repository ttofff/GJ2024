// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
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

//角色工具
UENUM(BlueprintType)
enum class ETools : uint8
{
	E_Hand UMETA(DisplayName = "Hand"),//空手
	E_Axe UMETA(DisplayName = "Axe"),//斧子
	E_Pickaxe UMETA(DisplayName = "Pickaxe"),//镐子
	E_Hammer UMETA(DisplayName = "Hammer"),//锤子
	E_Hoe UMETA(DisplayName = "Hoe")//锄头
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
	int32 StoneCnt = 0;//石头数量
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MineralCnt = 0;//矿物数量

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 FoodCnt = 0;//食物数量

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHaveAxe = false;//是否拥有斧子

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHavePickaxe = false;//是否拥有镐子

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHaveHammer = false;//是否拥有锤子

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHaveHoe = false;//是否拥有锄头
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive", meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractiveSphereCollision;

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
	ECharacterStates CharacterStates = ECharacterStates::E_Common;

	//背包信息
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PlayerBackpack")
	FBackpackInformation BackpackInfo;

	//工作台是否打开
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Workbench")
	bool bIsOpenedWorkbench = false;

	//工具种类
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tools")
	ETools ToolsType = ETools::E_Hand;

	//上一种工具种类
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tools")
	ETools LastToolsType = ETools::E_Hand;

	//是否生成工具
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tools")
	bool bIsSpawnTool = false;

	//工具Actor
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tools")
	AActor* ToolActor;

	//工作台合成信息
	TMap<FString, TArray<TPair<FString, int32>>> WorkTables
	{
		{TEXT("斧子"),{{TEXT("木材"), 1}, {TEXT("石头"), 1}, {TEXT("铁块"), 1}}},
		{TEXT("镐子"),{{TEXT("木材"), 1}, {TEXT("石头"), 2}}},
		{TEXT("锄头"),{{TEXT("木材"), 2}, {TEXT("石头"), 2}}}
	};

	
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

	void Interactive();

	void OpenBackpack();

	UFUNCTION(BlueprintCallable)
	bool CanProductItem(FString MaterialItemName, int32 MaterialCnt);

	UFUNCTION(BlueprintCallable)
	void ReduceMaterials(FString MaterialItemName, int32 MaterialCnt);

	UFUNCTION(BlueprintCallable)
	bool GetProductItem(FString ItemName);

	void UseAxe();

public:
	// Sets default values for this character's properties
	AGJCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//获取工作台合成信息
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetWorkTableItem(FText value) {return WorkTables[value.ToString()].Num();}

	//获取工作台合成材料名称
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetWorkTableMaterialName(FText value, int32 index) {return WorkTables[value.ToString()][index].Key; }

	//获取工作台合成材料数量
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetWorkTableMaterialCnt(FText value, int32 index) {return WorkTables[value.ToString()][index].Value; }
};
