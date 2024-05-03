// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_GetNextTargetFromArray.h"
#include "../../ASTurret.h"
#include "AIController.h"

EBTNodeResult::Type UASBTT_GetNextTargetFromArray::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* Controller = OwnerComp.GetAIOwner();

    Controller->GetPawn()->GetComponentByClass(AILocationComponent);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("InNext "));
    AASTurret* turret = Cast<AASTurret>(Controller->GetPawn());

    turret->Fire();

    //OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsOnTargetKey.SelectedKeyName, IsOnTarget);
    return EBTNodeResult::Type();
}
