// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "ASAICharacterController.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASAICharacterController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AIAction")
	bool FindTurretInWorld();

	UFUNCTION(BlueprintCallable, Category = "AIAction")
	void FindTurretbySight(AActor* actor, FAIStimulus stimulus);
};
