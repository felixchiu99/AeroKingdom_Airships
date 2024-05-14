// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ASDamageable/ASA_Target.h"
#include "ASA_TargetSpawner.generated.h"

class UASAC_WaypointComponent;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASA_TargetSpawner : public AActor
{
	GENERATED_BODY()
	
	/** Target class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<AASA_Target> TargetClass;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UASAC_WaypointComponent* WaypointComponent;

public:	
	// Sets default values for this actor's properties
	AASA_TargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnTarget();
};
