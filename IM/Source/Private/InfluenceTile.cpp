// Fill out your copyright notice in the Description page of Project Settings.


#include "InfluenceTile.h"

FInfluenceTile::FInfluenceTile(const FVector& Center) : Center{ Center }
{
}

float FInfluenceTile::GetValue() const noexcept
{
	return Value;
}

FVector FInfluenceTile::GetCenter() const noexcept
{
	return Center;
}

void FInfluenceTile::SetValue(const float& NewValue) noexcept
{
	Value = NewValue;
}
