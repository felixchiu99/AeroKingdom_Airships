// Fill out your copyright notice in the Description page of Project Settings.


#include "ASInteractablePawn.h"
#include "Components/ArrowComponent.h"

// Sets default values
AASInteractablePawn::AASInteractablePawn()
{
	// Create Tooltip Point
	TooltipDisplayPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TooltipDisplay"));
}

FVector AASInteractablePawn::GetTooltipDisplayPoint()
{
	if (HasTooltipDisplayPoint()) {
		return TooltipDisplayPoint->GetComponentLocation();
	}		
	else
		return FVector(0, 0, 0);
}

bool AASInteractablePawn::HasTooltipDisplayPoint()
{
	return TooltipDisplayPoint->IsValidLowLevel();
}

FText AASInteractablePawn::GetTooltipDisplayName()
{
	return TooltipLabelText;
}

void AASInteractablePawn::Possess(APawn* PossessingChar, AController* PossessingController)
{
	//Set Pointer to previous Chars
	PossessedChar = PossessingChar;
	PrevController = GetController();
	PrevAIController = Cast<AAIController>(GetController());

	// Unpossess current Controller
	PrevController->UnPossess();
	PossessingController->UnPossess();

	// Freeze/Unable Character
	EnableCharacter(false);

	//Possess This Pawn
	bIsCurrentlyPossessed = true;
	PossessingController->Possess(this);
}

void AASInteractablePawn::UnPossess(AController* SavedController)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, (SavedController == nullptr ? "True" : "False"));
	/* Unpossess current controller */
	if (SavedController)
	{
		SavedController->UnPossess();
		bIsCurrentlyPossessed = false;
	}

	/* Possess Character */
	if (PossessedChar) {
		MoveCharacter();
		EnableCharacter(true);
		SavedController->Possess(PossessedChar);
		PossessedChar = nullptr;
	}

	/* Give control Back to Prev controller*/
	/*
	if (PrevController) {
		PrevController->Possess(this);
		PrevController = nullptr;
	}
	*/

	if (PrevAIController) {
		PrevAIController->Possess(this);
		if (DefaultBehaviorTree) {
			PrevAIController->RunBehaviorTree(DefaultBehaviorTree);
		}
		PrevAIController = nullptr;
	}
}
