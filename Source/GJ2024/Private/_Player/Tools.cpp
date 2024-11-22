// Fill out your copyright notice in the Description page of Project Settings.


#include "_Player/Tools.h"

// Sets default values
ATools::ATools()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	ToolMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToolMeshComponent"));
	ToolMeshComponent->SetupAttachment(RootComponent);
	ToolMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ToolBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ToolBoxComponent"));
	ToolBoxComponent->SetupAttachment(ToolMeshComponent);
	ToolBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ATools::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATools::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);

}

