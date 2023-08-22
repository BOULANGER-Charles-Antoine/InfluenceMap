#pragma once

#include "CoreMinimal.h"
#include "InfluenceTile.h"
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
	TArray<FInfluenceTile> LayerValue{};

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
	const TArray<FInfluenceTile>& GetLayerValue() const noexcept;

	UFUNCTION()
	void CreateLayer(const FVector& Origin, const FVector& Extent, const FRotator& Rotation);

	UFUNCTION()
	void SetSizeLayer();

	TOptional<float> GetValueAtPosition(const FVector& Position);
	TOptional<float> GetValueAtIndex(const int& Index);

	void UpdateCenterCase(FVector& CenterCase, const FVector& CenterFirstCase, const int& Index);

private:
	void SetDimensions(const FVector& BoxExtentInfluenceMap);
	void SetOffset(const FVector& BoxOriginInfluenceMap);
	void InitializeLayerTiles(const FVector& Origin, const FVector& Extent, const FRotator& Rotation);
	FVector RotatePointAroundIM(const FVector& Point, const FVector& Origin, const FRotator& Rotation) const;

	int ConvertVector3DToIndex(const FVector& Position);
	FVector ConvertIndexToVector3D(const int& Index);
};
