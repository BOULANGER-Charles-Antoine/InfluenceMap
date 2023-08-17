// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfluenceLayer.generated.h"

// TODO : Helper class for Debug part

UCLASS(Blueprintable, BlueprintType)
class IM_API UInfluenceLayer : public UObject 
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, UIMin = 0, ForceUnits = "Meters"))
	int SizeCase{};

	UPROPERTY()
	TArray<float> MapValue{};

	UPROPERTY()
	FVector DimensionsLayer{};
	UPROPERTY()
	FVector OffsetMap{};
	UPROPERTY()
	int SizeLayer;
	UPROPERTY()
	int SizeLayerXY;

public:
	UInfluenceLayer();

	int GetSizeCase() const noexcept;

	UFUNCTION()
	void CreateLayer(const FBoxSphereBounds& BoxBounds);

	UFUNCTION()
	void SetSizeLayer();

	TOptional<float> GetValue(const FVector& Position);
	TOptional<float> GetValue(const int& Index);

	void Debug(UWorld* World, const FBoxSphereBounds& BoxBounds);
	void UpdateCenterCaseDebug(FVector& CenterCaseDebug, const FVector& CenterFirstCaseDebug, const int& Index);

private:
	void SetDimensions(const FVector& BoxExtentInfluenceMap);
	void SetOffset(const FVector& BoxOriginInfluenceMap);
	void InitializeMapValue();

	int ConvertVector3DToIndex(const FVector& Position);
	FVector ConvertIndexToVector3D(const int& Index);

	// TODO : operator [] instead of GetValue
};
