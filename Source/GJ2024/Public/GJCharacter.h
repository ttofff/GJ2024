// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Sound/SoundCue.h"
#include "GJCharacter.generated.h"

//角色状态
UENUM(BlueprintType)
enum class ECharacterStates : uint8
{
	E_Common UMETA(DisplayName = "Common"),//普通状态
	E_Jump UMETA(DisplayName = "Jump"),//跳跃状态
	E_Attack UMETA(DisplayName = "Attack"),//攻击状态
	E_Build UMETA(DisplayName = "Build"),//建造状态
	E_Interaction UMETA(DisplayName = "Interaction"),//交互状态
	E_OpenBackpack UMETA(DisplayName = "OpenBackpack"),//打开背包状态
	E_OpenChangeMesh UMETA(DisplayName = "OpenChangeMesh"),//打开变身状态
	E_ChangeMesh UMETA(DisplayName = "ChangeMesh"),//变身状态
	E_SelectChangeMesh UMETA(DisplayName = "SelectChangeMesh"),//选择变身状态
	E_OpenTransfer UMETA(DisplayName = "OpenTransfer")//打开传送状态
};

//角色工具
UENUM(BlueprintType)
enum class ETools : uint8
{
	E_Hand UMETA(DisplayName = "Hand"),//空手
	E_Axe UMETA(DisplayName = "Axe"),//斧子
	E_Pickaxe UMETA(DisplayName = "Pickaxe"),//镐子
	E_Hammer UMETA(DisplayName = "Hammer")//锤子
};

UENUM(BlueprintType)
enum class EBackpackClass : uint8
{
	Wood UMETA(DisplayName = "Wood"),//木材
	Stone UMETA(DisplayName = "Stone"),//石头
	Iron UMETA(DisplayName = "Iron"),//铁矿
	Food UMETA(DisplayName = "Food"),//食物
	Axe UMETA(DisplayName = "Axe"),//斧子
	Pickaxe UMETA(DisplayName = "Pickaxe"),//镐子
	Hammer UMETA(DisplayName = "Hammer"),//锤子
	Mushroom UMETA(DisplayName = "Mushroom")//蘑菇
};

//角色变身种类
UENUM(BlueprintType)
enum class EChangeClass : uint8
{
	E_Human UMETA(DisplayName = "Human"),//人类
	E_Cat UMETA(DisplayName = "Cat"),//猫
	E_Tree UMETA(DisplayName = "Tree"),//树
	E_Stone UMETA(DisplayName = "Stone"),//石头
	E_Sheep UMETA(DisplayName = "Sheep"),//羊
	E_Cloud UMETA(DisplayName = "Cloud"),//云
	E_Flower UMETA(DisplayName = "Flower"),//花
	E_Coconut UMETA(DisplayName = "Coconut")//椰子
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
	int32 IronCnt = 0;//铁矿数量

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 FoodCnt = 0;//食物数量

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MushroomCnt = 3;//蘑菇数量

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHaveAxe = false;//是否拥有斧子

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHavePickaxe = false;//是否拥有镐子

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHaveHammer = false;//是否拥有锤子

};

UCLASS()
class GJ2024_API AGJCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* PlayerCameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* FollowCameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* InteractiveBoxCollision;

	//改变角色模型的粒子系统
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "NiagaraComponent", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* ChangeMeshNiagaraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "ChangeMesh", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ChangeMeshSceneComponent;

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
	float AcceleratedSpeed = 600.f;

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

	//背包是否打开
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Backpack")
	bool bIsOpenedBackpack = false;

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

	//是否打开背包
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	bool IsOpenBackpack = false;

	//是否打开变身
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	bool IsOpenChangeMesh = false;

	//是否已经打开变身
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	bool IsOpenedChangeMesh = false;

	//是否打开传送
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	bool IsOpenTransfer = false;

	//是否已经打开传送
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	bool IsOpenedTransfer = false;

	//快捷栏是否为空
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tools")
	TArray<bool> ShortcutIsEmpty;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tools")
	int32 CurrentShortcutIndex = -1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tools")
	int32 LastShortcutIndex = -1;

	//变身粒子特效
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "NiagaraComponent")
	UNiagaraSystem* ChangeMeshNiagaraSystem;

	//变身类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeClass")
	TArray<EChangeClass> ChangeClassType_Keys =
		{EChangeClass::E_Human, EChangeClass::E_Human, EChangeClass::E_Human};

	//当前变身类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeClass")
	EChangeClass CurrentChangeClassType = EChangeClass::E_Human;

	//模型数组
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ChangeMesh")
	TArray<USkeletalMesh*> ChangeMeshArray;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ChangeMesh")
	TArray<UClass*> ChangeMeshArrayAnims;

	bool bIsChangingMesh = false;//是否正在变身

	//是否在自动移动
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AutoMoving")
	bool bIsAutoMoving = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	bool bIsOpenSelectChangeMesh = false;

	//是否已经打开选择变身界面
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	bool bIsClosedSelectChangeMesh = false;

	//是否可以重新开始
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Restart")
	bool bCanRestart = false;

	//重新开始位置
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Restart")
	FTransform RestartTransform;

	//是否可以飞行
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Fly")
	bool bIsFly = false;

	//飞行速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Fly")
	float FlySpeed = 600.f;

	//变身时间
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	float ChangeMeshTime = 40.f;

	//最长变身时间
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	float MaxChangeMeshTime = 40.f;

	//是否产生石头
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	bool IsSpawnStone = false;

	//是否产生木头
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	bool IsSpawnTree = false;
	
	FTimerHandle ChangeMeshTimerHandle;

	//变身冷却时间
	FTimerHandle CoolingChangeMeshTimerHandle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	TArray<FVector> TransferLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ChangeMesh")
	TArray<FText> TransferName;

	//前进
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement")
	bool bIsMoveForward = false;

	//左右
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement")
	bool bIsMoveRight = false;

	// //是否在走直线上
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement")
	// bool bIsGoStraight = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement")
	int32 DirectionIndex = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement")		
	FTransform CampTransform;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BGM")
	UAudioComponent* BGMComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BGM")
	TArray<USoundBase*> BGM;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BGM")
	int32 CurrentMusicIndex = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sequence")
	bool IsSequence = false;
	
	//工作台合成信息
	TMap<FString, TArray<TPair<FString, int32>>> WorkTables
	{
		{TEXT("斧子"),{{TEXT("木材"), 1}, {TEXT("石头"), 1}, {TEXT("铁块"), 1}}},
		{TEXT("镐子"),{{TEXT("木材"), 1}, {TEXT("石头"), 2}}},
		{TEXT("锄头"),{{TEXT("木材"), 2}, {TEXT("石头"), 2}}},
		{TEXT("锤子"),{{TEXT("木材"), 3}, {TEXT("石头"), 3}}}
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

	void UsedShortcut(int32 Index);
	
	void UsedShortcut_1();

	void UsedShortcut_2();

	void UsedShortcut_3();

	void OpenChangeMesh();

	void ChangeMesh(EChangeClass ChangeClassType);

	UFUNCTION(BlueprintCallable)
	void ChangeMesh_1();

	UFUNCTION(BlueprintCallable)
	void ChangeMesh_2();

	void ChangeMesh_3();

	void Fly(float DeltaTime);

	void StartRecordChangeMeshTime();

	void StartRecordCoolingChangeMeshTime();

	void PlayNextMusic();
	
public:
	// Sets default values for this character's properties
	AGJCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FVector CalculateDirectionToAngle(const FVector& Direction);

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
