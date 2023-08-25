#include "InfluenceLayer.h"
#include "InfluenceTile.h"

UInfluenceLayer::UInfluenceLayer()
{
}

void UInfluenceLayer::SetDimensions(const FVector& BoxExtentInfluenceMap)
{
	const int X = FMath::CeilToInt(BoxExtentInfluenceMap.X / SizeCase);
	const int Y = FMath::CeilToInt(BoxExtentInfluenceMap.Y / SizeCase);
	const int Z = FMath::CeilToInt(BoxExtentInfluenceMap.Z / SizeCase);

	DimensionsLayer = FVector{ FMath::Max(X, 1.0), FMath::Max(Y, 1.0),FMath::Max(Z, 1.0) };
}

void UInfluenceLayer::SetOffset(const FVector& BoxOriginInfluenceMap)
{
	OffsetMap = BoxOriginInfluenceMap;
}

void UInfluenceLayer::InitializeLayerTiles(const FVector& Origin, const FVector& Extent, const FRotator& Rotation)
{
	LayerValue.SetNum(SizeLayer);
	
	InitializeCenterTiles(Origin, Extent, Rotation);

	LayerValue[2].SetValue(1.5486f);
}

void UInfluenceLayer::InitializeCenterTiles(const FVector& Origin, const FVector& Extent, const FRotator& Rotation)
{
	const FVector OffsetCase = Rotation.RotateVector(FVector{ static_cast<double>(SizeCase) });
	FVector CenterCase = Origin - Extent;
	const FVector CenterFirstCase = Origin - Extent;

	for (int i = 0; i != SizeLayer; ++i) 
	{
		LayerValue[i] = FInfluenceTile{ RotatePointAroundIM(CenterCase, FTransform(Origin), Rotation) + OffsetCase };

		UpdateCenterCase(CenterCase, CenterFirstCase, i);
	}
}

FVector UInfluenceLayer::RotatePointAroundIM(const FVector& Point, const FTransform& Transform, const FRotator& Rotation) const
{
	FVector RotatedPoint = Transform.InverseTransformPosition(Point);
	RotatedPoint = Rotation.RotateVector(RotatedPoint);

	return Transform.TransformPosition(RotatedPoint);
}

void UInfluenceLayer::UpdateCenterCase(FVector& CenterCase, const FVector& CenterFirstCase, const int& Index)
{
	if ((Index + 1) % SizeLayerXY == 0)
	{
		CenterCase.X = CenterFirstCase.X;
		CenterCase.Y = CenterFirstCase.Y;

		CenterCase.Z += 2 * SizeCase;
	}
	else if ((Index + 1) % static_cast<int>(DimensionsLayer.X) == 0)
	{
		CenterCase.X = CenterFirstCase.X;

		CenterCase.Y += 2 * SizeCase;
	}
	else
	{
		CenterCase.X += 2 * SizeCase;
	}
}

int UInfluenceLayer::ConvertVector3DToIndex(const FVector& Position)
{
	return Position.X + DimensionsLayer.X * Position.Y + DimensionsLayer.X * DimensionsLayer.Y * Position.Z;
}

FVector UInfluenceLayer::ConvertIndexToVector3D(const int& Index)
{
	double Z = Index / (DimensionsLayer.X * DimensionsLayer.Y);
	double Y = Z / DimensionsLayer.X;
	double X = Z - Y * DimensionsLayer.X;

	return FVector{ X, Y, Z };
}

void UInfluenceLayer::CreateLayer(const FVector& Origin, const FVector& Extent, const FRotator& Rotation)
{
	SetDimensions(Extent);
	SetOffset(Origin);
	SetSizeLayer();
	InitializeLayerTiles(Origin, Extent, Rotation);
}

FString UInfluenceLayer::GetName()
{
	return Name;
}

void UInfluenceLayer::SetSizeLayer()
{
	SizeLayerXY = DimensionsLayer.X * DimensionsLayer.Y;
	SizeLayer = SizeLayerXY * DimensionsLayer.Z;
}

TOptional<float> UInfluenceLayer::GetValueAtPosition(const FVector& Position)
{
	return GetValueAtIndex(ConvertVector3DToIndex(Position));
}

TOptional<float> UInfluenceLayer::GetValueAtIndex(const int& Index)
{
	return LayerValue.IsValidIndex(Index) ? TOptional<float>{ LayerValue[Index].GetValue() } : TOptional<float>{};
}

int UInfluenceLayer::GetSizeCase() const noexcept
{
	return SizeCase;
}

const TArray<FInfluenceTile>& UInfluenceLayer::GetLayerValue() const noexcept
{
	return LayerValue;
}
