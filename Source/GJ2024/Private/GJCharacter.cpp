// Fill out your copyright notice in the Description page of Project Settings.


#include "GJCharacter.h"

#include "../../../../../UE5/UE_5.2/Engine/Plugins/Experimental/NNE/Source/ThirdParty/onnxruntime/Dependencies/gsl/gsl-lite.hpp"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGJCharacter::AGJCharacter():
RotationRate(0.3f),
ArmLengthValue(10.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;//移动朝向运动

	PlayerCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	PlayerCameraSpringArm->SetupAttachment(RootComponent);
	PlayerCameraSpringArm->bUsePawnControlRotation = true;

	FollowCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FollowCameraSpringArm"));
	FollowCameraSpringArm->SetupAttachment(PlayerCameraSpringArm);
	FollowCameraSpringArm->TargetArmLength = 0.f;
	FollowCameraSpringArm->bUsePawnControlRotation = false;
	FollowCameraSpringArm->bDoCollisionTest = false;
	FollowCameraSpringArm->bEnableCameraLag = true;
	FollowCameraSpringArm->bEnableCameraRotationLag = true;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(FollowCameraSpringArm);
	PlayerCamera->bUsePawnControlRotation = false;

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	AttackBox->SetupAttachment(RootComponent);
	AttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractiveBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractiveBoxCollision"));
	InteractiveBoxCollision->SetupAttachment(GetMesh());
	InteractiveBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ChangeMeshNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ChangeMeshNiagara"));
	ChangeMeshNiagaraComponent->SetupAttachment(GetMesh());
	ChangeMeshNiagaraComponent->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AGJCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGJCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGJCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	
	//基本操作
	PlayerInputComponent->BindAxis("Look", this, &AGJCharacter::Look);
	PlayerInputComponent->BindAxis("Turn", this, &AGJCharacter::Turn);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AGJCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGJCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("Accelerated", IE_Pressed, this, &AGJCharacter::Accelerate);
	PlayerInputComponent->BindAction("Accelerated", IE_Released, this, &AGJCharacter::Decelerate);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGJCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AGJCharacter::StopJumping);

	PlayerInputComponent->BindAxis("SpringArmLength", this, &AGJCharacter::ModifyArmLength);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AGJCharacter::Attack);

	PlayerInputComponent->BindAction("Interactive", IE_Pressed, this, &AGJCharacter::Interactive);

	PlayerInputComponent->BindAction("OpenBackpack", IE_Pressed, this, &AGJCharacter::OpenBackpack);
	PlayerInputComponent->BindAction("OpenChangeMesh", IE_Pressed, this, &AGJCharacter::OpenChangeMesh);
	
	PlayerInputComponent->BindAction("UsedShortcut_1", IE_Pressed, this, &AGJCharacter::UsedShortcut_1);
	PlayerInputComponent->BindAction("UsedShortcut_2", IE_Pressed, this, &AGJCharacter::UsedShortcut_2);
	PlayerInputComponent->BindAction("UsedShortcut_3", IE_Pressed, this, &AGJCharacter::UsedShortcut_3);

	PlayerInputComponent->BindAction("ChangeMesh_1", IE_Pressed, this, &AGJCharacter::ChangeMesh_1);
	PlayerInputComponent->BindAction("ChangeMesh_2", IE_Pressed, this, &AGJCharacter::ChangeMesh_2);
	
}

//上下移动视角
void AGJCharacter::Look(float value)
{
	if(CharacterStates == ECharacterStates::E_Interaction || CharacterStates == ECharacterStates::E_Build) return;//防止交互时移动
	float NewValue = ClampCameraRotation + value * RotationRate;
	if (NewValue <= 40.f && NewValue >=0.f)
	{
		ClampCameraRotation = NewValue;
		AddControllerPitchInput(value * RotationRate);
	}
	else
	{
		if (NewValue > 40.f)
		{
			ClampCameraRotation = 40.f;
		}
		else ClampCameraRotation = 0.f;
	}
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
	// 			FString::Printf(TEXT("ClampCameraRotation：%f"),ClampCameraRotation));
}

//左右移动视角
void AGJCharacter::Turn(float value)
{
	if(CharacterStates == ECharacterStates::E_Interaction || CharacterStates == ECharacterStates::E_Build) return;//防止交互时移动
	AddControllerYawInput(value * RotationRate);
}

//前后移动
void AGJCharacter::MoveForward(float value)
{
	if(CharacterStates == ECharacterStates::E_Interaction || CharacterStates == ECharacterStates::E_Build || bIsChangingMesh) return;//防止交互时移动
	if ((Controller != nullptr) || (value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

//左右移动
void AGJCharacter::MoveRight(float value)
{
	if(CharacterStates == ECharacterStates::E_Interaction || CharacterStates == ECharacterStates::E_Build || bIsChangingMesh) return;//防止交互时移动
	if ((Controller != nullptr) || (value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

//加速
void AGJCharacter::Accelerate()
{
	GetCharacterMovement()->MaxWalkSpeed = AcceleratedSpeed;
}

//减速
void AGJCharacter::Decelerate()
{
	GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;
}

//跳跃
void AGJCharacter::Jump()
{
	if(bCanRestart) return;
	ACharacter::Jump();
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
	// 	FString::Printf(TEXT("JumpCurrentCount：%d"),JumpCurrentCount));
}

//停止跳跃
void AGJCharacter::StopJumping()
{
	if(bCanRestart) return;
	ACharacter::StopJumping();
}

//修改弹簧臂长度
void AGJCharacter::ModifyArmLength(float value)
{
	if(CharacterStates != ECharacterStates::E_Common) return;
	float ClampLength = FMath::Clamp(value * ArmLengthValue + PlayerCameraSpringArm->TargetArmLength, 300.f, 800.f);
	PlayerCameraSpringArm->TargetArmLength = ClampLength;
}

//攻击
void AGJCharacter::Attack()
{
	if(CharacterStates != ECharacterStates::E_Common) return;//防止攻击时再次攻击
	
	AttackBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterStates = ECharacterStates::E_Attack;

	AttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FTimerHandle AttackTimerHandle;
	GetWorldTimerManager().SetTimer(AttackTimerHandle,[this]()
	{
		CharacterStates = ECharacterStates::E_Common;
	},.5f,false);
}

//交互物品
void AGJCharacter::Interactive()
{
	if(CharacterStates != ECharacterStates::E_Common && CharacterStates != ECharacterStates::E_Interaction) return;

	InteractiveBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	InteractiveBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

//打开背包
void AGJCharacter::OpenBackpack()
{
	if(CharacterStates != ECharacterStates::E_Common && CharacterStates != ECharacterStates::E_OpenBackpack) return;
	IsOpenBackpack = true;
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("BackpackInfo.WoodCnt: %d"),BackpackInfo.WoodCnt));
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("BackpackInfo.StoneCnt: %d"),BackpackInfo.StoneCnt));
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("BackpackInfo.IronCnt: %d"),BackpackInfo.IronCnt));
}

//判断背包中是否有足够的材料
bool AGJCharacter::CanProductItem(FString MaterialItemName, int32 MaterialCnt)
{
	bool bCanProduct = true;
	if (MaterialItemName == TEXT("木材"))
		bCanProduct = BackpackInfo.WoodCnt >= MaterialCnt;
	else if(MaterialItemName == TEXT("石头"))
		bCanProduct = BackpackInfo.StoneCnt >= MaterialCnt;
	else if(MaterialItemName == TEXT("铁块"))
		bCanProduct = BackpackInfo.IronCnt >= MaterialCnt;
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("CanProductItem：%d"), bCanProduct));
	return bCanProduct;
}

//消耗材料
void AGJCharacter::ReduceMaterials(FString MaterialItemName, int32 MaterialCnt)
{
	if (MaterialItemName == TEXT("木材"))
		BackpackInfo.WoodCnt -= MaterialCnt;
	else if(MaterialItemName == TEXT("石头"))
		BackpackInfo.StoneCnt -= MaterialCnt;
	else if(MaterialItemName == TEXT("铁块"))
		BackpackInfo.IronCnt -= MaterialCnt;
}

//得到物品
bool   AGJCharacter::GetProductItem(FString ItemName)
{
	bool bHaveItem = false;//判断是否已经拥有该工具
	if (ItemName == TEXT("斧子"))
		bHaveItem = BackpackInfo.bHaveAxe = true;
	else if (ItemName == TEXT("锤子"))
		bHaveItem = BackpackInfo.bHaveHammer = true;
	else if(ItemName == TEXT("镐子"))
		bHaveItem = BackpackInfo.bHavePickaxe = true;

	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("BackpackInfo.bHaveAxe：%d"), BackpackInfo.bHaveAxe));
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("BackpackInfo.bHaveHammer：%d"), BackpackInfo.bHaveHammer));
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("BackpackInfo.bHavePickaxe：%d"), BackpackInfo.bHavePickaxe));
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("BackpackInfo.bHaveHoe：%d"), BackpackInfo.bHaveHoe));

	return bHaveItem;
}

//使用快捷键
void AGJCharacter::UsedShortcut(int32 Index)
{
	if (!ShortcutIsEmpty[Index])
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("ShortcutIsEmpty[Index]：%d"), ShortcutIsEmpty[Index]));
		if (ToolActor == nullptr)
		{
			CurrentShortcutIndex = Index;//记录当前快捷键的索引
			LastShortcutIndex = Index;//记录上一个快捷键的索引
			bIsSpawnTool = true;
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("ToolActor == nullptr")));
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("ToolActor != nullptr")));
			ToolActor->Destroy();//销毁上一个的工具
			ToolActor = nullptr;
			
			if(LastShortcutIndex != Index)
			{
				CurrentShortcutIndex = Index;//记录当前快捷键的索引
				LastShortcutIndex = Index;//记录上一个快捷键的索引
				bIsSpawnTool = true;
			}
			else
			{
				CurrentShortcutIndex = -1;//记录当前快捷键的索引
			}
		}
	}
}

//使用快捷键1
void AGJCharacter::UsedShortcut_1()
{
	if(CharacterStates != ECharacterStates::E_Common) return;
	UsedShortcut(0);
}

//使用快捷键2
void AGJCharacter::UsedShortcut_2()
{
	if(CharacterStates != ECharacterStates::E_Common) return;
	UsedShortcut(1);
}

//使用快捷键3
void AGJCharacter::UsedShortcut_3()
{
	if(CharacterStates != ECharacterStates::E_Common) return;
	UsedShortcut(2);
}

//变身
void AGJCharacter::OpenChangeMesh()
{
	if(CharacterStates != ECharacterStates::E_Common && CharacterStates != ECharacterStates::E_OpenChangeMesh) return;
	IsOpenChangeMesh = true;
}

//变身
void AGJCharacter::ChangeMesh(EChangeClass ChangeClassType)
{
	int32 Index = -1;
	switch (ChangeClassType)
	{
		case EChangeClass::E_Human: Index = 0; break; //人
		case EChangeClass::E_Cat: Index = 1; break; //猫
		case EChangeClass::E_Tree: Index = 2; break; //树
		case EChangeClass::E_Stone: Index = 3; break; //石头
	}
	
	//变身
	if (ChangeMeshNiagaraSystem && ChangeMeshNiagaraComponent
		&& ChangeMeshArray[Index])
	{
		ChangeMeshNiagaraComponent->SetAsset(ChangeMeshNiagaraSystem);
		ChangeMeshNiagaraComponent->Activate();

		bIsChangingMesh = true;
			
		FTimerHandle ChangeMeshTimerHandle;
		GetWorldTimerManager().SetTimer(ChangeMeshTimerHandle,[this, Index]()
		{
			GetMesh()->SetSkeletalMesh(ChangeMeshArray[Index]);
			GetMesh()->SetAnimClass(ChangeMeshArrayAnims[Index]);
			FTimerHandle ChangeMeshTimerHandle2;
			GetWorldTimerManager().SetTimer(ChangeMeshTimerHandle2,[this]()
			{
				ChangeMeshNiagaraComponent->Deactivate();
				bIsChangingMesh = false; //变身完成
			},0.2f,false);
		},1.f,false);
		
	}
}

//选择1变身
void AGJCharacter::ChangeMesh_1()
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
	// 	FString::Printf(TEXT("ChangeClassType_1Key: %s"),*UEnum::GetValueAsString(ChangeClassType_1Key)));
	if (CharacterStates == ECharacterStates::E_Common && ChangeClassType_1Key != EChangeClass::E_Human)
	{
		CharacterStates = ECharacterStates::E_ChangeMesh; //变身状态
		ChangeMesh(ChangeClassType_1Key);
	}
	else if (CharacterStates == ECharacterStates::E_ChangeMesh)
	{
		CharacterStates = ECharacterStates::E_Common; //变身状态
		ChangeMesh(EChangeClass::E_Human);
	}
	
}

//选择2变身
void AGJCharacter::ChangeMesh_2()
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
	// FString::Printf(TEXT("ChangeClassType_2Key: %s"),*UEnum::GetValueAsString(ChangeClassType_2Key)));
	if (CharacterStates == ECharacterStates::E_Common && ChangeClassType_2Key != EChangeClass::E_Human)
	{
		CharacterStates = ECharacterStates::E_ChangeMesh; //变身状态
		ChangeMesh(ChangeClassType_2Key);
	}
	else if (CharacterStates == ECharacterStates::E_ChangeMesh)
	{
		CharacterStates = ECharacterStates::E_Common; //变身状态
		ChangeMesh(EChangeClass::E_Human);
	}
}



