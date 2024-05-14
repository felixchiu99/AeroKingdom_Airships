// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTS_UpdateTargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"

UASBTS_UpdateTargetLocation::UASBTS_UpdateTargetLocation() {
	NodeName = "UpdateTargetLocation";
}

void UASBTS_UpdateTargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (!TargetActor) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No"));
		//OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasTargetKey.SelectedKeyName, false);
		return;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AimTargetKey.SelectedKeyName, TargetActor->GetTargetLocation());
}
