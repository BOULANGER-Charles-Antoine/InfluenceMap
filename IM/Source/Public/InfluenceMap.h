// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfluenceMap.generated.h"

USTRUCT()
struct FIMPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInfluenceLayer> Layer{};
};

UCLASS()
class IM_API AInfluenceMap : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FIMPair> InfluenceMap{};
protected:
	UPROPERTY(BlueprintReadOnly)
	FRotator IMRotation{};

	UPROPERTY(BlueprintReadOnly)
	FVector IMDimension{};

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* LimitsInfluenceMap{};
	
private:
	FVector RotatePointAroundIM(const FVector& Point);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AInfluenceMap();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Debug();
};
