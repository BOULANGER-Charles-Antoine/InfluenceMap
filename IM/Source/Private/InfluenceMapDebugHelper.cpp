#include "InfluenceMapDebugHelper.h"

#include "InfluenceMap.h"
#include "InfluenceLayer.h"
#include "Algo/ForEach.h"

void InfluenceMapDebugHelper::ShowInfluenceMapDebug(const AInfluenceMap* InfluenceMap, const FString& NameLayer)
{
	const FIMPair* IMPair = Algo::FindBy(InfluenceMap->GetLayers(), NameLayer, &FIMPair::Name);

	if(IMPair)
	{
		TSubclassOf<UInfluenceLayer> Layer = IMPair->Layer;

		FVector VectorSizeCase{ static_cast<double>(Layer.GetDefaultObject()->GetSizeCase()) };

		int Index = 0;
		Algo::ForEach(Layer.GetDefaultObject()->GetLayerValue(), [&](const FInfluenceTile& InfluenceTile) 
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
