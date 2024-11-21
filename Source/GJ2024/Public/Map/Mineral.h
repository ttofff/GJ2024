// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FallingObjects.h"
#include "Mineral.generated.h"

UCLASS()
class GJ2024_API AMineral : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mineral", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mineral", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MineralMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree", meta = (AllowPrivateAccess = "true"))
	USceneComponent* FallingObjectsSceneSpawn;
	
public:
	//矿物要开采的次数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mineral")
	int32 MineralHealCnt = 3;

	//矿物信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mineral")
	FItemInfo MineralItemInfo;

	//是否可以采集
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mineral")
	bool bIsSpawnFallingObjects = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Mineral")
	void GatherMinerals();

public:
	// Sets default values for this actor's properties
	AMineral();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
