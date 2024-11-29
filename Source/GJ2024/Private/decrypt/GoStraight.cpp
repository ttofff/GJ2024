// Fill out your copyright notice in the Description page of Project Settings.


#include "decrypt/GoStraight.h"

#include "GJCharacter.h"

// Sets default values
AGoStraight::AGoStraight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(RootComponent);

	UpBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("UpBoxComponent"));
	UpBoxComponent->SetupAttachment(BoxMesh);
	UpBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	CrossingMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrossingMeshComponent"));
	CrossingMeshComponent->SetupAttachment(RootComponent);
	CrossingMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// Called when the game starts or when spawned
void AGoStraight::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGoStraight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


