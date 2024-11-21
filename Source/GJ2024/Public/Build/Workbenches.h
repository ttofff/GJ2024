// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Workbenches.generated.h"

UCLASS()
class GJ2024_API AWorkbenches : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Workbench", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WorkbenchMeshComponent;
	
public:	
	// Sets default values for this actor's properties
	AWorkbenches();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
