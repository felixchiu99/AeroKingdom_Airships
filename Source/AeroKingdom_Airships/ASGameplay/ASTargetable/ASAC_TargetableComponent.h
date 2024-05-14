// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASI_Targetable.h"
#include "ASAC_TargetableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEROKINGDOM_AIRSHIPS_API UASAC_TargetableComponent : public UActorComponent, public IASI_Targetable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASAC_TargetableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FVector GetLocation() override;
};
