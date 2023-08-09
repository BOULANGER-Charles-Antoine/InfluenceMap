// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfluenceLayer.generated.h"

UCLASS(Blueprintable, BlueprintType)
class IM_API UInfluenceLayer : public UObject 
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, UIMin = 0, Units = "Meters"))
	int SizeCase;

	UPROPERTY()
	TArray<int> MapValue;

public:
	UInfluenceLayer();
};
