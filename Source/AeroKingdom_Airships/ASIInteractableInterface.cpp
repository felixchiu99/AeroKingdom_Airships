// Fill out your copyright notice in the Description page of Project Settings.


#include "ASIInteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

void IASIInteractableInterface::Possess(APawn* PossessingChar)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ( PossessingChar==nullptr ? "True" : "False"));
	PossessedChar = PossessingChar;
	EnableCharacter(false);
	bIsCurrentlyPossessed = true;
}

void IASIInteractableInterface::UnPossess(AController* SavedController)
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
	}
}

bool IASIInteractableInterface::IsPossessed()
{
	return bIsCurrentlyPossessed;
}

void IASIInteractableInterface::MoveCharacter()
{
}

void IASIInteractableInterface::EnableCharacter(bool enabled)
{
	PossessedChar->SetActorTickEnabled(enabled);
	PossessedChar->SetActorHiddenInGame(!enabled);
	PossessedChar->SetActorEnableCollision(enabled);
}
