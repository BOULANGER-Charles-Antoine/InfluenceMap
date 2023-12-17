#include "InfluenceMap.h"

#include "InfluenceLayer.h"
#include "InfluenceMapDebugHelper.h"
#include "Algo/ForEach.h"
#include "Components/StaticMeshComponent.h"

AInfluenceMap::AInfluenceMap()
{
	PrimaryActorTick.bCanEverTick = false;

	CreateLimits();
}

void AInfluenceMap::CreateLimits()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh = TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'");

	if (CubeMesh.Succeeded())
	{
		LimitsInfluenceMap = CreateDefaultSubobject<UStaticMeshComponent>(FName("Limit Influence Map"));
		LimitsInfluenceMap->SetStaticMesh(Cast<UStaticMesh>(CubeMesh.Object));
		LimitsInfluenceMap->SetCollisionResponseToAllChannels(ECR_Ignore);
		LimitsInfluenceMap->SetupAttachment(RootComponent);
	}
}

const TArray<TSubclassOf<UInfluenceLayer>>& AInfluenceMap::GetLayers() const noexcept
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

	Algo::ForEach(InfluenceMap, [&](TSubclassOf<UInfluenceLayer>& Layer)
	{
		Layer.GetDefaultObject()->CreateLayer(LimitsInfluenceMap->Bounds.Origin, IMDimension, IMRotation);
	});

	Debug("Test2");

	Debug("Branch1");
}

void AInfluenceMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AInfluenceMap::Debug(const FString& NameLayer)
{
	InfluenceMapDebugHelper::ShowInfluenceMapDebug(this, NameLayer);
}

