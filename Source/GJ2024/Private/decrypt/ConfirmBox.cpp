// Fill out your copyright notice in the Description page of Project Settings.


#include "decrypt/ConfirmBox.h"

#include "decrypt/PushBox.h"

// Sets default values
AConfirmBox::AConfirmBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	ConfirmBoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConfirmBoxMeshComponent"));
	ConfirmBoxMeshComponent->SetupAttachment(RootComponent);

	ConfirmBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ConfirmBoxComponent"));
	ConfirmBoxComponent->SetupAttachment(ConfirmBoxMeshComponent);
	ConfirmBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
}

// Called when the game starts or when spawned
void AConfirmBox::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AConfirmBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

