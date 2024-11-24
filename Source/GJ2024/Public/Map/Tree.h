// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FallingObjects.h"
#include "Tree.generated.h"

UCLASS()
class GJ2024_API ATree : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TreeTrunkMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TreeRootMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TreeCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree", meta = (AllowPrivateAccess = "true"))
	USceneComponent* FallingObjectsSceneSpawn;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Tree")
	int32 TreeHealCnt = 3;
	
	// UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Tree")
	// FItemInfo TreeItemInfo;

	//是否砍倒
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Tree")
	bool bIsSpawn = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Tree")
	float FallTreePower = 120.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Tree")
	FRotator FallingDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Tree")
	void ChopDownTree(AActor* Player);

public:
	// Sets default values for this actor's properties
	ATree();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
