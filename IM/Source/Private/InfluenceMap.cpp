// Fill out your copyright notice in the Description page of Project Settings.

#include "InfluenceMap.h"

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

// Called when the game starts or when spawned
void AInfluenceMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInfluenceMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

