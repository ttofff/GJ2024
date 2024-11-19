// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Tree.h"
#include "GJCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	
	TreeTrunkMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeTrunkMeshComponent"));
	TreeTrunkMeshComponent->SetupAttachment(RootComponent);
	
	TreeRootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeRootMeshComponent"));
	TreeRootMeshComponent->SetupAttachment(RootComponent);

	TreeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TreeCollisionComponent"));
	TreeCollision->SetupAttachment(TreeTrunkMeshComponent);

	FallingObjectsSceneSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("FallingObjectsSceneSpawn"));
	FallingObjectsSceneSpawn->SetupAttachment(TreeTrunkMeshComponent);
	
}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	
}

//砍树
void ATree::ChopDownTree(AActor* Player)
{
	AGJCharacter* GJPlayer = Cast<AGJCharacter>(Player);
	if(--TreeHealCnt <= 0 && GJPlayer)
	{
		TreeCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TreeTrunkMeshComponent->SetSimulatePhysics(true);
		
		const FVector RightDirection = GJPlayer->GetActorRightVector() * -FallTreePower;
		const FVector ForwardDirection = GJPlayer->GetActorForwardVector() * FallTreePower;
		
		FVector Direction = FMath::RandBool()? ForwardDirection : ForwardDirection + RightDirection;//随机方向
		//冲量
		TreeTrunkMeshComponent->AddImpulse(Direction, NAME_None, true);
		
		FTimerHandle DelayTimerHandle;
		GetWorldTimerManager().SetTimer(DelayTimerHandle, [this]()
		{
			bIsChoppedDown = true;
		}, 4.f, false);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChopDownTree")));
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

