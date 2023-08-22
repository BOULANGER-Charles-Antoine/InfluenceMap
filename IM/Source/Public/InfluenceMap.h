#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfluenceMap.generated.h"

USTRUCT()
struct FIMPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInfluenceLayer> Layer{};
};

UCLASS()
class IM_API AInfluenceMap : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FIMPair> InfluenceMap{};

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool ShowZeroDebug{};

protected:
	UPROPERTY(BlueprintReadOnly)
	FRotator IMRotation{};

	UPROPERTY(BlueprintReadOnly)
	FVector IMDimension{};

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* LimitsInfluenceMap{};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AInfluenceMap();

	const TArray<FIMPair>& GetLayers() const noexcept;
	bool GetShowZeroDebug() const noexcept;
	FRotator GetIMRotation() const noexcept;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Debug(const FString& NameLayer);
};
