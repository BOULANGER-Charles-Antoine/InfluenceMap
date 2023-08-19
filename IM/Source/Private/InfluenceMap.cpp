// Fill out your copyright notice in the Description page of Project Settings.

#include "InfluenceMap.h"

#include "InfluenceLayer.h"
#include "Algo/ForEach.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInfluenceMap::AInfluenceMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LimitsInfluenceMap = CreateDefaultSubobject<UStaticMeshComponent>(FName("Limit Influence Map"));
	if(ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh = (TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")); CubeMesh.Succeeded())
	{
		LimitsInfluenceMap->SetStaticMesh(Cast<UStaticMesh>(CubeMesh.Object));
		LimitsInfluenceMap->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	LimitsInfluenceMap->SetupAttachment(RootComponent);
}

FVector AInfluenceMap::RotatePointAroundIM(const FVector& Point)
{
	FTransform TransformedOrigin = UKismetMathLibrary::Conv_VectorToTransform(LimitsInfluenceMap->Bounds.Origin);

	FVector RotatedPoint = UKismetMathLibrary::InverseTransformLocation(TransformedOrigin, Point);
	RotatedPoint = IMRotation.RotateVector(RotatedPoint);

	return UKismetMathLibrary::TransformLocation(TransformedOrigin, RotatedPoint);
}

// Called when the game starts or when spawned
void AInfluenceMap::BeginPlay()
{
	Super::BeginPlay();

	IMRotation = GetActorRotation();
	SetActorRotation(FRotator::ZeroRotator);
	IMDimension = LimitsInfluenceMap->Bounds.BoxExtent;
	SetActorRotation(IMRotation);

	Algo::ForEach(InfluenceMap, [&](FIMPair& IMPair)
	{
		IMPair.Layer.GetDefaultObject()->CreateLayer(LimitsInfluenceMap->Bounds.Origin, IMDimension);
	});

	Debug();
}

// Called every frame
void AInfluenceMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AInfluenceMap::Debug()
{
	// Find Layer then ...
	auto Layer = InfluenceMap[0].Layer;

	FVector VectorSizeCase{ static_cast<double>(Layer.GetDefaultObject()->GetSizeCase()) };
	FVector CenterCaseDebug = LimitsInfluenceMap->Bounds.Origin - IMDimension;
	FVector CenterCaseDebugRotated = RotatePointAroundIM(CenterCaseDebug) + IMRotation.RotateVector(VectorSizeCase);
	const FVector CenterFirstCaseDebug = CenterCaseDebug;

	int Index = 0;
	Algo::ForEach(Layer.GetDefaultObject()->GetLayerValue(), [&](const float& Value) 
	{
		DrawDebugBox(GetWorld(), CenterCaseDebugRotated, VectorSizeCase, IMRotation.Quaternion(), FColor::Blue, true);
		DrawDebugString(GetWorld(), CenterCaseDebugRotated, FString::Printf(TEXT("%f\n%d"), Value, Index)); // TODO : fix format float Value

		Layer.GetDefaultObject()->UpdateCenterCaseDebug(CenterCaseDebug, CenterFirstCaseDebug, ++Index);
		CenterCaseDebugRotated = RotatePointAroundIM(CenterCaseDebug) + IMRotation.RotateVector(VectorSizeCase);
	});
}

