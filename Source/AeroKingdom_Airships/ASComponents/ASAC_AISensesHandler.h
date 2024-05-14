// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "ASAC_AISensesHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEROKINGDOM_AIRSHIPS_API UASAC_AISensesHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASAC_AISensesHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleStimulus(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	virtual void HandleSight(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	virtual void HandleHearing(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	virtual void HandleTouch(AActor* Actor, FAIStimulus Stimulus);
	
	UFUNCTION(BlueprintCallable)
	virtual void HandlePrediction(AActor* Actor, FAIStimulus Stimulus);
};
