// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingBall.generated.h"

UCLASS(Abstract)
class AEROKINGDOM_AIRSHIPS_API ARollingBall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Ball;
public:	
	// Sets default values for this actor's properties
	ARollingBall(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidgetComp;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	float Health;
	float MaxHealth = 100;

};
