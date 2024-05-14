// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTS_SortTurretTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../ASTurret.h"
#include "../../ASComponents/ASAC_TurretTargetList.h"

UASBTS_SortTurretTarget::UASBTS_SortTurretTarget() {
	NodeName = "SortTurretTarget";
}

void UASBTS_SortTurretTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* SelfController = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelfActorKey.SelectedKeyName));
	if (!SelfController) {
		return;
	}

	AAIController* AiController = Cast<AAIController>(SelfController);
	if (!AiController) {
		return;
	}

	AASTurret* Turret = Cast<AASTurret>(AiController->GetPawn());
	if (!Turret) {
		return;
	}

	UASAC_TurretTargetList* TargetList = Turret->GetTargetList();
	if (!TargetList) {
		return;
	}
	TargetList->CalculateTarget();

	AActor* CalculatedTarget = TargetList->GetCalulatedTarget();
	if (!CalculatedTarget) {
		return;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("cal " + CalculatedTarget->GetActorLocation().ToCompactString()));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasTargetKey.SelectedKeyName, true);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetActorKey.SelectedKeyName, CalculatedTarget);

}
