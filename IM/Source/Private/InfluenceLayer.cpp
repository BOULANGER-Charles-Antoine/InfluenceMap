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
	MapValue.SetNumZeroed(SizeMap());
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

void UInfluenceLayer::CreateLayer(const FBoxSphereBounds& BoxBounds)
{
	// TODO : attention au rotation de la map
	SetDimensions(BoxBounds.BoxExtent);
	SetOffset(BoxBounds.Origin);
	InitializeMapValue();
}

int UInfluenceLayer::SizeMap()
{
	return DimensionsLayer.X * DimensionsLayer.Y * DimensionsLayer.Z;
}

TOptional<float> UInfluenceLayer::GetValue(const FVector& Position)
{
	TOptional<float> Value{};

	FVector DistanceOriginMapPosition = Position - OffsetMap;
	if((Position.X >= 0 && Position.X <= DimensionsLayer.X * SizeCase) && 
	   (Position.Y >= 0 && Position.Y <= DimensionsLayer.Y * SizeCase) &&
	   (Position.Z >= 0 && Position.Z <= DimensionsLayer.Z * SizeCase))
	{
		Value.Emplace(MapValue[ConvertVector3DToIndex(Position)]);
	}

	return Value;
}

TOptional<float> UInfluenceLayer::GetValue(const int& Index)
{
	return TOptional<float>{};
}

void UInfluenceLayer::Debug(UWorld* World, const FBoxSphereBounds& BoxBounds)
{
	FVector OriginCaseDebug = BoxBounds.Origin - BoxBounds.BoxExtent + SizeCase;
	FVector OriginMapDebug = OriginCaseDebug;
	FVector RealSizeCase{ static_cast<double>(SizeCase), static_cast<double>(SizeCase), static_cast<double>(SizeCase) };

	int Index = 0;
	Algo::ForEach(MapValue, [&](const int& Value) 
	{
		DrawDebugBox(World, OriginCaseDebug, RealSizeCase, FColor::Blue, true, 60, 0, 1);
		DrawDebugString(World, OriginCaseDebug - SizeCase / 10, FString::Printf(TEXT("%d\n%d"), Value, Index), 0, FColor::White, 10, false, 1);

		++Index;
		if(Index % static_cast<int>(DimensionsLayer.X * DimensionsLayer.Y) == 0)
		{
			OriginCaseDebug.X = OriginMapDebug.X;
			OriginCaseDebug.Y = OriginMapDebug.Y;
			OriginCaseDebug.Z += 2 * SizeCase;
		}
		else if(Index % static_cast<int>(DimensionsLayer.X) == 0)
		{
			OriginCaseDebug.X = OriginMapDebug.X;
			OriginCaseDebug.Y += 2 * SizeCase;
		}
		else
		{
			OriginCaseDebug.X += 2 * SizeCase;
		}
	});
}

int UInfluenceLayer::GetSizeCase() const noexcept
{
	return SizeCase;
}
