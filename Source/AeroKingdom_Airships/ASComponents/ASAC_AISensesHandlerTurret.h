// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAC_AISensesHandler.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "ASAC_AISensesHandlerTurret.generated.h"

class IASI_Targetable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEROKINGDOM_AIRSHIPS_API UASAC_AISensesHandlerTurret : public UASAC_AISensesHandler
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASAC_AISensesHandlerTurret();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HandleSight(AActor* Actor, FAIStimulus Stimulus) override;

	float CalculateScore(IASI_Targetable* Target);

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FName AimTargetKey = "AimTarget";

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FName TargetActorKey = "TargetActor";

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FName HasFireControlInputKey = "HasFireControlInput";

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FName HasTargetLabel = "HasTarget";
};
