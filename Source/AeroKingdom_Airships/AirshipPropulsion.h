// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirshipPropulsion.generated.h"

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AAirshipPropulsion : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* EngineCore;
public:	
	// Sets default values for this actor's properties
	AAirshipPropulsion();

public:	
	virtual void ApplyThrust();

	float fThrustForce = 30000.f;
};
