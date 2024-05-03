// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_TurretFire.h"
#include "../../ASTurret.h"
#include "AIController.h"

EBTNodeResult::Type UASBTT_TurretFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    AAIController* Controller = OwnerComp.GetAIOwner();

    AASTurret* turret = Cast<AASTurret>(Controller->GetPawn());

    turret->Fire();

    //OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsOnTargetKey.SelectedKeyName, IsOnTarget);

	return EBTNodeResult::Type();
}
