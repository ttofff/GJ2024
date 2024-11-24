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
	SphereComponent->SetupAttachment(FallingObjectsMeshComponent);

}

// Called when the game starts or when spawned
void AFallingObjects::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFallingObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

