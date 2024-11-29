// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "OneStroke.generated.h"

UCLASS()
class GJ2024_API AOneStroke : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OneStroke", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OneStroke", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OneStroke", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* UpBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OneStroke", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BlockBoxComponent;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "OneStroke")
	bool bIsStepped = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "OneStroke")
	bool IsEnd = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "OneStroke")
	bool bIsCheck = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "OneStroke")
	UMaterialInterface* OriginalMaterial;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties`
	AOneStroke();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
