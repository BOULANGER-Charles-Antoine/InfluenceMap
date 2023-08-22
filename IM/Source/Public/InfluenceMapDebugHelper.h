#pragma once

#include "CoreMinimal.h"

class AInfluenceMap;

class IM_API InfluenceMapDebugHelper
{
public:
	InfluenceMapDebugHelper() = default;
	~InfluenceMapDebugHelper() = default;

	static void ShowInfluenceMapDebug(const AInfluenceMap* InfluenceMap, const FString& NameLayer);
	static void ShowDebugValue(const UWorld* World, const float& Value, const FVector& CenterCaseDebug);
};
