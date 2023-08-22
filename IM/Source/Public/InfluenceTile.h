// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfluenceTile.generated.h"

USTRUCT()
struct IM_API FInfluenceTile
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float Value{};

	UPROPERTY()
	FVector Center{};

public:
	FInfluenceTile() = default;
	FInfluenceTile(const FVector& Center);
	~FInfluenceTile() = default;

	float GetValue() const noexcept;
	FVector GetCenter() const noexcept;

	void SetValue(const float& NewValue) noexcept;
};
