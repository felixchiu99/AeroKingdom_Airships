// Fill out your copyright notice in the Description page of Project Settings.


#include "ASIInteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

void IASIInteractableInterface::Possess(APawn* PossessingChar, AController* PossessingController)
{
}

void IASIInteractableInterface::UnPossess(AController* SavedController)
{
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
