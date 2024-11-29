// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BoxTeleport.generated.h"

UCLASS()
class GJ2024_API ABoxTeleport : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoxTeleport", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoxTeleport", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;
	
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BoxTeleport", meta = (MakeEditWidget = "true"))
	FVector TeleportLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ABoxTeleport();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
