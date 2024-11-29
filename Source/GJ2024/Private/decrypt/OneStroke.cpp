// Fill out your copyright notice in the Description page of Project Settings.


#include "decrypt/OneStroke.h"

// Sets default values
AOneStroke::AOneStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(RootComponent);

	UpBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("UpBoxComponent"));
	UpBoxComponent->SetupAttachment(BoxMesh);

	BlockBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockBoxComponent"));
	BlockBoxComponent->SetupAttachment(BoxMesh);
	
}

// Called when the game starts or when spawned
void AOneStroke::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOneStroke::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

