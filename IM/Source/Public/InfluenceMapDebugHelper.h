#pragma once

#include "CoreMinimal.h"
#include "InfluenceMapDebugHelper.generated.h"

class AInfluenceMap;

USTRUCT()
struct IM_API FInfluenceMapDebugHelperParameters
{
	GENERATED_BODY()

	FString NameLayer;

	FInfluenceMapDebugHelperParameters() = default;
};

class IM_API InfluenceMapDebugHelper
{
public:
	InfluenceMapDebugHelper() = default;
	~InfluenceMapDebugHelper() = default;

	static void ShowInfluenceMapDebug(const AInfluenceMap* InfluenceMap, const FString& NameLayer);
	static void ShowDebugValue(const UWorld* World, const float& Value, const FVector& CenterCaseDebug);
};
