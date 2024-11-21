// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/FallingObjects.h"
#include "GJCharacter.h"

// Sets default values
AFallingObjects::AFallingObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	FallingObjectsMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FallingObjectsMeshComponent"));
	FallingObjectsMeshComponent->SetupAttachment(RootComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFallingObjects::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFallingObjects::OnOverlapBegin);
	
}

//组件开始重叠
void AFallingObjects::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Pickup"));
		//装进背包
		AGJCharacter* Player = Cast<AGJCharacter>(OtherActor);
		if (Player)
		{
			switch (ItemInfo.FallingObjectsType)
			{
				case EFallingObjects::ECS_Tree:
					{
						Player->BackpackInfo.WoodCnt += ItemInfo.Cnt;
						Player->BackpackInfo.BackpackWeight -= ItemInfo.Cnt;
						break;
					}
				case EFallingObjects::ECS_Stone:
					{
						Player->BackpackInfo.StoneCnt += ItemInfo.Cnt;
						Player->BackpackInfo.BackpackWeight -= ItemInfo.Cnt;
						break;
					}
				case EFallingObjects::ECS_Mineral:
					{
						Player->BackpackInfo.MineralCnt += ItemInfo.Cnt;
						Player->BackpackInfo.BackpackWeight -= ItemInfo.Cnt;
						break;	
					}
				case EFallingObjects::ECS_Food:
					{
						Player->BackpackInfo.FoodCnt += ItemInfo.Cnt;
						Player->BackpackInfo.BackpackWeight -= ItemInfo.Cnt;
						break;
					}
			}
			Destroy();
		}
	}
}

// Called every frame
void AFallingObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

