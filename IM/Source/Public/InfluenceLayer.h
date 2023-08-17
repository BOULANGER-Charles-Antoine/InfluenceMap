// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfluenceLayer.generated.h"

UCLASS(Blueprintable, BlueprintType)
class IM_API UInfluenceLayer : public UObject 
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, UIMin = 0, ForceUnits = "Meters"))
	int SizeCase{};

	UPROPERTY()
	TArray<int> MapValue{};

	UPROPERTY()
	FVector DimensionsLayer{};
	UPROPERTY()
	FVector OffsetMap{};

public:
	UInfluenceLayer();

	int GetSizeCase() const noexcept;

	UFUNCTION()
	void CreateLayer(const FBoxSphereBounds& BoxBounds);

	UFUNCTION()
	int SizeMap();

	TOptional<float> GetValue(const FVector& Position);
	TOptional<float> GetValue(const int& Index);
	void Debug(class UWorld* World, const FBoxSphereBounds& BoxBounds);

private:
	void SetDimensions(const FVector& BoxExtentInfluenceMap);
	void SetOffset(const FVector& BoxOriginInfluenceMap);
	void InitializeMapValue();

	int ConvertVector3DToIndex(const FVector& Position);
	FVector ConvertIndexToVector3D(const int& Index);

	// TODO : operator [] instead of GetValue
};
