// Fill out your copyright notice in the Description page of Project Settings.


#include "Build/Workbenches.h"

// Sets default values
AWorkbenches::AWorkbenches()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	WorkbenchMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorkbenchMeshComponent"));
	WorkbenchMeshComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AWorkbenches::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorkbenches::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

