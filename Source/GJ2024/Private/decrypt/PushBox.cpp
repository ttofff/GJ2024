// Fill out your copyright notice in the Description page of Project Settings.


#include "decrypt/PushBox.h"

// Sets default values
APushBox::APushBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(RootComponent);

	ForwardBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ForwardBoxComponent"));
	ForwardBoxComponent->SetupAttachment(BoxMesh);

	BackBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BackBoxComponent"));
	BackBoxComponent->SetupAttachment(BoxMesh);

	RightBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RightBoxComponent"));
	RightBoxComponent->SetupAttachment(BoxMesh);

	LeftBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftBoxComponent"));
	LeftBoxComponent->SetupAttachment(BoxMesh);
	
}

// Called when the game starts or when spawned
void APushBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

