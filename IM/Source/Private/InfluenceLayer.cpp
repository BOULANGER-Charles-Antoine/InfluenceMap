// Fill out your copyright notice in the Description page of Project Settings.

#include "InfluenceLayer.h"

#include "Algo/ForEach.h"

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

void UInfluenceLayer::InitializeMapValue()
{
	LayerValue.SetNumZeroed(SizeLayer);
	LayerValue[2] = 1.5486f;
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

void UInfluenceLayer::CreateLayer(const FVector& Origin, const FVector& Extent)
{
	// TODO : attention au rotation de la map
	SetDimensions(Extent);
	SetOffset(Origin);
	SetSizeLayer();
	InitializeMapValue();
}

void UInfluenceLayer::SetSizeLayer()
{
	SizeLayerXY = DimensionsLayer.X * DimensionsLayer.Y;
	SizeLayer = SizeLayerXY * DimensionsLayer.Z;
}

TOptional<float> UInfluenceLayer::GetValue(const FVector& Position)
{
	TOptional<float> Value{};
	
	if((Position.X >= OffsetMap.X && Position.X <= DimensionsLayer.X * SizeCase) && 
	   (Position.Y >= OffsetMap.Y && Position.Y <= DimensionsLayer.Y * SizeCase) &&
	   (Position.Z >= OffsetMap.Z && Position.Z <= DimensionsLayer.Z * SizeCase))
	{
		Value.Emplace(LayerValue[ConvertVector3DToIndex(Position)]);
	}

	return Value;
}

TOptional<float> UInfluenceLayer::GetValue(const int& Index)
{
	return Index >= 0 && Index < SizeLayer ? TOptional<float>{LayerValue[Index]} : TOptional<float>{};
}

void UInfluenceLayer::Debug(UWorld* World, const FBoxSphereBounds& BoxBounds)
{
	FVector CenterCaseDebug = BoxBounds.Origin - BoxBounds.BoxExtent + SizeCase;
	const FVector CenterFirstCaseDebug = CenterCaseDebug;
	FVector VectorSizeCase{ static_cast<double>(SizeCase), static_cast<double>(SizeCase), static_cast<double>(SizeCase) };

	int Index = 0;
	Algo::ForEach(LayerValue, [&](const int& Value) 
	{
		DrawDebugBox(World, CenterCaseDebug, VectorSizeCase, FColor::Blue, true);
		DrawDebugString(World, CenterCaseDebug - SizeCase / 10, FString::Printf(TEXT("%d\n%d"), Value, Index));
		
		UpdateCenterCaseDebug(CenterCaseDebug, CenterFirstCaseDebug, ++Index);
	});
}

void UInfluenceLayer::UpdateCenterCaseDebug(FVector& CenterCaseDebug, const FVector& CenterFirstCaseDebug, const int& Index)
{
	if (Index % SizeLayerXY == 0) 
	{
		CenterCaseDebug.X = CenterFirstCaseDebug.X;
		CenterCaseDebug.Y = CenterFirstCaseDebug.Y;
		CenterCaseDebug.Z += 2 * SizeCase;
	}
	else if (Index % static_cast<int>(DimensionsLayer.X) == 0)
	{
		CenterCaseDebug.X = CenterFirstCaseDebug.X;
		CenterCaseDebug.Y += 2 * SizeCase;
	}
	else 
	{
		CenterCaseDebug.X += 2 * SizeCase;
	}
}

int UInfluenceLayer::GetSizeCase() const noexcept
{
	return SizeCase;
}

const TArray<float>& UInfluenceLayer::GetLayerValue() const noexcept
{
	return LayerValue;
}
