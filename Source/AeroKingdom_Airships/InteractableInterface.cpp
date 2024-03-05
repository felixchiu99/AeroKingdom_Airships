// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

void IInteractableInterface::Possess(APawn* PossessingChar)
{
	PossessedChar = PossessingChar;
}

void IInteractableInterface::UnPossess(AController* SavedController)
{
	/* Unpossess current controller */
	SavedController->UnPossess();

	/* Possess Character */
	SavedController->Possess(PossessedChar);
}