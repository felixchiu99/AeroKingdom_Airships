// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASA_DamageableActor.h"
#include "ASA_Target.generated.h"

class UASAC_WaypointComponent;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASA_Target : public AASA_DamageableActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* TargetMesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UASAC_WaypointComponent* WaypointComponent;

public:	
	// Sets default values for this actor's properties
	AASA_Target();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWaypointComponent(UASAC_WaypointComponent* WPComponent);

protected:
	void MoveToWaypoint();
	void CheckArrivedWaypoint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MoveSpeed = 1.0f;
};
