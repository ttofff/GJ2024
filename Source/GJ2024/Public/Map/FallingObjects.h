// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "FallingObjects.generated.h"

//掉落物种类
UENUM(BlueprintType)
enum class EFallingObjects : uint8
{
	ECS_Tree UMETA (DisplayName = "Tree"),//树
	ECS_Stone UMETA (DisplayName = "Stone"),//石头
	ECS_Mineral UMETA (DisplayName = "Mineral"),//矿物
	ECS_Food UMETA (DisplayName = "Food")//食物
};

//掉落物信息
USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EFallingObjects FallingObjectsType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Cnt = 0;
};

UCLASS()
class GJ2024_API AFallingObjects : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FallingObjects", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FallingObjects", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FallingObjectsMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FallingObjects", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "FallingObjectsItem")
	FItemInfo ItemInfo;

	FRotator RotationRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Sets default values for this actor's properties
	AFallingObjects();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
