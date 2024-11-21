// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Mineral.h"

// Sets default values
AMineral::AMineral()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	MineralMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineralMeshComponent"));
	MineralMeshComponent->SetupAttachment(RootComponent);

	FallingObjectsSceneSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("FallingObjectsSceneSpawn"));
	FallingObjectsSceneSpawn->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AMineral::BeginPlay()
{
	Super::BeginPlay();
	
}

//开采矿物
void AMineral::GatherMinerals()
{
	if (--MineralHealCnt <= 0 && !bIsSpawnFallingObjects)
	{
		bIsSpawnFallingObjects = true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("GatherMinerals")));
}

// Called every frame
void AMineral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

