// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAICharacterController.h"
#include "../../ASTurret.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

bool AASAICharacterController::FindTurretInWorld()
{
	if (!Blackboard) {
		return false;
	}

	return false;
}

void AASAICharacterController::FindTurretbySight(AActor* actor, FAIStimulus stimulus)
{
	if (!Blackboard) {
		return;
	}

	//Return if sensed object is turret
	AASTurret* turret = Cast<AASTurret>(actor);
	if (!turret) {
		return;
	}
	
	//Return if stimulus is not sight
	FAISenseID sightid = UAISense::GetSenseID<UAISense_Sight>();
	if (stimulus.Type != sightid) {
		return;
	}

	//Set Target
	if (stimulus.IsActive()) {
		GetBlackboardComponent()->SetValueAsObject("TargetActor", Cast<AActor>(turret));
	}
	else {
		GetBlackboardComponent()->SetValueAsObject("TargetActor",nullptr);
	}

	//Set Last position
	if (stimulus.WasSuccessfullySensed()) {
		GetBlackboardComponent()->SetValueAsObject("TargetActor", Cast<AActor>(turret));
	}
	else {
		GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
		GetBlackboardComponent()->SetValueAsVector("LastKnownLocation", stimulus.StimulusLocation);
	}
}
