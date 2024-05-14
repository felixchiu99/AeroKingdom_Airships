// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAC_AISensesHandlerTurret.h"
#include "../ASGameplay/ASTargetable/ASI_Targetable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../ASTurret.h"
#include "ASAC_TurretTargetList.h"

// Sets default values for this component's properties
UASAC_AISensesHandlerTurret::UASAC_AISensesHandlerTurret()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UASAC_AISensesHandlerTurret::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UASAC_AISensesHandlerTurret::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UASAC_AISensesHandlerTurret::HandleSight(AActor* Actor, FAIStimulus Stimulus)
{
	TArray<UActorComponent*> Components = Actor->GetComponentsByInterface(UASI_Targetable::StaticClass());
	if (Components.IsEmpty()) {
		return;
	}

	/*
	TMultiMap <float, FVector> Locations;
	for (UActorComponent* Component : Components)
	{
		IASI_Targetable* Target = Cast<IASI_Targetable>(Component);
		if (Target)
		{
			float Score = CalculateScore(Target);
			FVector loc = Target->GetLocation();
			Locations.Add(Score,loc);
		}
	}

	//Locations.KeySort()

	FVector FinalLocation = Locations.begin()->Value;
	*/
	AAIController* AiController = Cast<AAIController>(GetOwner());
	if (!AiController) {
		return;
	}

	bool HasFireDirector = AiController->GetBlackboardComponent()->GetValueAsBool(HasFireControlInputKey);
	bool HasTarget = AiController->GetBlackboardComponent()->GetValueAsBool(HasTargetLabel);

	if (HasTarget && HasFireDirector) {
		return;
	}

	AASTurret* Turret = Cast<AASTurret>(AiController->GetPawn());

	if (!Turret) {
		return;
	}

	Turret->GetTargetList()->AddTarget(Actor);
	//AActor* TempTarget = Turret->GetTargetList()->GetCalulatedTarget();
	/*
	if(score){
		change target
	}
	*/

	//AiController->GetBlackboardComponent()->SetValueAsVector(AimTargetKey, FinalLocation);
	//AiController->GetBlackboardComponent()->SetValueAsObject(TargetActorKey, TempTarget);

}

float UASAC_AISensesHandlerTurret::CalculateScore(IASI_Targetable* Target)
{
	if (Target) {
		float fDist = FMath::FloorToInt(FVector::Dist(
			GetOwner()->GetActorLocation(),
			Target->GetLocation()
		));
		return fDist;
	}
	return 0;
}

