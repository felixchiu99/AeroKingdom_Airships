// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASAC_AIShipWaypointSystem.generated.h"

class UASAC_WaypointComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEROKINGDOM_AIRSHIPS_API UASAC_AIShipWaypointSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASAC_AIShipWaypointSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UASAC_WaypointComponent* GetCheckpointSystem();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	UASAC_WaypointComponent* CheckpointSystem;
};
