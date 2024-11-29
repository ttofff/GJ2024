// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ConfirmBox.generated.h"

UCLASS()
class GJ2024_API AConfirmBox : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ConfirmBox", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ConfirmBox", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConfirmBoxMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ConfirmBox", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* ConfirmBoxComponent;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ConfirmBox")
	bool bIsHaveBox = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AConfirmBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
