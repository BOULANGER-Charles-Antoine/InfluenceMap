// Fill out your copyright notice in the Description page of Project Settings.

#include "InfluenceMap.h"

#include "InfluenceLayer.h"
#include "Algo/ForEach.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInfluenceMap::AInfluenceMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LimitsInfluenceMap = CreateDefaultSubobject<UStaticMeshComponent>(FName("Limit Influence Map"));
	if(ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh = (TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")); CubeMesh.Succeeded())
	{
		LimitsInfluenceMap->SetStaticMesh(Cast<UStaticMesh>(CubeMesh.Object));
	}
	LimitsInfluenceMap->SetupAttachment(RootComponent);
}

FVector AInfluenceMap::OffsetMap()
{
	return LimitsInfluenceMap->Bounds.Origin;
}

// Called when the game starts or when spawned
void AInfluenceMap::BeginPlay()
{
	Super::BeginPlay();

	Algo::ForEach(InfluenceMap, [&](FIMPair& Pair)
	{
		Pair.Layer.GetDefaultObject()->CreateLayer(LimitsInfluenceMap->Bounds.BoxExtent);
	});
	
	FVector OriginTest = OffsetMap(); // test
}

// Called every frame
void AInfluenceMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

