// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GoStraight.generated.h"

UCLASS()
class GJ2024_API AGoStraight : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GoStraight", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GoStraight", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GoStraight", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* UpBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GoStraight", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CrossingMeshComponent;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GoStraight")
	UMaterialInterface* OriginalMaterial;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AGoStraight();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
