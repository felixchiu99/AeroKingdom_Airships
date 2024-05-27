// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASAC_WaypointComponent.generated.h"

class AASA_WaypointActor;

UENUM(BlueprintType)
enum class TransverseDirection:uint8
{
	Loop,
	PingPong,
	None
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEROKINGDOM_AIRSHIPS_API UASAC_WaypointComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<AASA_WaypointActor*> WaypointsActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<FVector> WaypointVectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TransverseDirection Direction{TransverseDirection::Loop };

public:	
	// Sets default values for this component's properties
	UASAC_WaypointComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWaypointActors(TArray<AASA_WaypointActor*> InWaypointActors);
	//TArray<AASA_WaypointActor*> GetWaypoints();

	TArray<FVector> GetWaypoints();
	void SetWaypoints(TArray<FVector> InWaypoints);
	void AddWaypoints(FVector InWaypoint);
	void EmptyWaypoints();

	//AASA_WaypointActor* GetWaypoint();
	FVector GetWaypoint();
	FVector GetWaypointLocation();

	void NextIndex();

protected:
	void InitWaypointVectorsFromActor();

protected:
	int32 CurrentIndex = 0;

	bool bIsDecreasing = false;
};
