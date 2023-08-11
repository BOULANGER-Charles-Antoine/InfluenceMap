// Fill out your copyright notice in the Description page of Project Settings.

#include "InfluenceLayer.h"

#include "Algo/ForEach.h"

UInfluenceLayer::UInfluenceLayer()
{
}

void UInfluenceLayer::SetDimensions(const FVector& BoxExtentInfluenceMap)
{
	const int X = BoxExtentInfluenceMap.X / SizeCase;
	const int Y = BoxExtentInfluenceMap.Y / SizeCase;
	const int Z = BoxExtentInfluenceMap.Z / SizeCase;

	DimensionsLayer = FVector{ FMath::Max(X, 1.0), FMath::Max(Y, 1.0),FMath::Max(Z, 1.0) };
}

void UInfluenceLayer::InitializeMapValue()
{
	Algo::ForEach(MapValue, [&](auto& Value)
	{
		Value = {};
	});
}

void UInfluenceLayer::CreateLayer(const FVector& BoxExtentInfluenceMap)
{
	SetDimensions(BoxExtentInfluenceMap);
	MapValue.Reserve(SizeMap());
	InitializeMapValue();
}

int UInfluenceLayer::SizeMap()
{
	return DimensionsLayer.X * DimensionsLayer.Y * DimensionsLayer.Z;
}

int UInfluenceLayer::GetSizeCase() const noexcept
{
	return SizeCase;
}
