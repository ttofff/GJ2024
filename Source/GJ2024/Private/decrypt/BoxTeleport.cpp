// Fill out your copyright notice in the Description page of Project Settings.


#include "decrypt/BoxTeleport.h"

// Sets default values
ABoxTeleport::ABoxTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABoxTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

