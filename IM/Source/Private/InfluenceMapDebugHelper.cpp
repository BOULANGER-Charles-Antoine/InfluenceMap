#include "InfluenceMapDebugHelper.h"

#include "InfluenceMap.h"
#include "InfluenceLayer.h"
#include "Algo/ForEach.h"

void InfluenceMapDebugHelper::ShowInfluenceMapDebug(const AInfluenceMap* InfluenceMap, const FString& NameLayer)
{
	auto IMLayer = Algo::FindByPredicate(InfluenceMap->GetLayers(), [&](const TSubclassOf<UInfluenceLayer>& Layer)
	{
		return Layer.GetDefaultObject()->GetName() == NameLayer;
	});

	if(IMLayer)
	{
		FVector VectorSizeCase{ static_cast<double>(IMLayer->GetDefaultObject()->GetSizeCase()) };

		int Index = 0;
		Algo::ForEach(IMLayer->GetDefaultObject()->GetLayerValue(), [&](const FInfluenceTile& InfluenceTile)
		{
			DrawDebugBox(InfluenceMap->GetWorld(), InfluenceTile.GetCenter(), VectorSizeCase, InfluenceMap->GetIMRotation().Quaternion(), FColor::Blue, true);

			if (InfluenceTile.GetValue() > 0.001f || InfluenceTile.GetValue() <= 0.001 && InfluenceMap->GetShowZeroDebug())
			{
				ShowDebugValue(InfluenceMap->GetWorld(), InfluenceTile.GetValue(), InfluenceTile.GetCenter());
			}
		});
	}
}

void InfluenceMapDebugHelper::ShowDebugValue(const UWorld* World, const float& Value, const FVector& CenterCaseDebug)
{
	FNumberFormattingOptions NumberFormat;
	NumberFormat.MinimumIntegralDigits = 1;
	NumberFormat.MaximumIntegralDigits = 10000;
	NumberFormat.MinimumFractionalDigits = 0;
	NumberFormat.MaximumFractionalDigits = 2;

	DrawDebugString(World, CenterCaseDebug, FText::AsNumber(Value, &NumberFormat).ToString());
}
