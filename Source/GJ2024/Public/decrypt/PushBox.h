// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PushBox.generated.h"

UCLASS()
class GJ2024_API APushBox : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PushBox", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PushBox", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PushBox", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* ForwardBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PushBox", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BackBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PushBox", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* RightBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PushBox", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* LeftBoxComponent;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Restart")
	FVector StartLocation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	APushBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
