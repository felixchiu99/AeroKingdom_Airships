// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

void IInteractableInterface::Possess(APawn* PossessingChar)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ( PossessingChar==nullptr ? "True" : "False"));
	PossessedChar = PossessingChar;
}

void IInteractableInterface::UnPossess(AController* SavedController)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, (SavedController == nullptr ? "True" : "False"));
	/* Unpossess current controller */
	if (SavedController)
		SavedController->UnPossess();

	/* Possess Character */
	if(PossessedChar)
		SavedController->Possess(PossessedChar);
}