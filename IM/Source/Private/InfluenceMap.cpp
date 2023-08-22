#include "InfluenceMap.h"

#include "InfluenceLayer.h"
#include "InfluenceMapDebugHelper.h"
#include "InfluenceTile.h"
#include "Algo/ForEach.h"
#include "Components/StaticMeshComponent.h"


AInfluenceMap::AInfluenceMap()
{
	PrimaryActorTick.bCanEverTick = false;

	LimitsInfluenceMap = CreateDefaultSubobject<UStaticMeshComponent>(FName("Limit Influence Map"));
	if(ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh = TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"); CubeMesh.Succeeded())
	{
		LimitsInfluenceMap->SetStaticMesh(Cast<UStaticMesh>(CubeMesh.Object));
		LimitsInfluenceMap->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	LimitsInfluenceMap->SetupAttachment(RootComponent);
}

const TArray<FIMPair>& AInfluenceMap::GetLayers() const noexcept
{
	return InfluenceMap;
}

bool AInfluenceMap::GetShowZeroDebug() const noexcept
{
	return ShowZeroDebug;
}

FRotator AInfluenceMap::GetIMRotation() const noexcept
{
	return IMRotation;
}


void AInfluenceMap::BeginPlay()
{
	Super::BeginPlay();

	IMRotation = GetActorRotation();
	SetActorRotation(FRotator::ZeroRotator);
	IMDimension = LimitsInfluenceMap->Bounds.BoxExtent;
	SetActorRotation(IMRotation);

	Algo::ForEach(InfluenceMap, [&](FIMPair& IMPair)
	{
		IMPair.Layer.GetDefaultObject()->CreateLayer(LimitsInfluenceMap->Bounds.Origin, IMDimension, IMRotation);
	});

	Debug("Test2");
}

void AInfluenceMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AInfluenceMap::Debug(const FString& NameLayer)
{
	InfluenceMapDebugHelper::ShowInfluenceMapDebug(this, NameLayer);
}

