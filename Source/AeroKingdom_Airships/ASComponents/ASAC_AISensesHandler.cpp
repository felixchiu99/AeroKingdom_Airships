// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAC_AISensesHandler.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Prediction.h"
#include "Perception/AISense_Touch.h"

// Sets default values for this component's properties
UASAC_AISensesHandler::UASAC_AISensesHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UASAC_AISensesHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UASAC_AISensesHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UASAC_AISensesHandler::HandleStimulus(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>()) {
		HandleSight(Actor, Stimulus);
	}
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>()) {
		HandleHearing(Actor, Stimulus);
	}
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Touch>()) {
		HandleTouch(Actor, Stimulus);
	}
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Prediction>()) {
		HandlePrediction(Actor, Stimulus);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Type " + FString::SanitizeFloat(Stimulus.Type)));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sight Type " + FString::SanitizeFloat(UAISense::GetSenseID<UAISense_Sight>())));
}

void UASAC_AISensesHandler::HandleSight(AActor* Actor, FAIStimulus Stimulus)
{
}

void UASAC_AISensesHandler::HandleHearing(AActor* Actor, FAIStimulus Stimulus)
{
}

void UASAC_AISensesHandler::HandleTouch(AActor* Actor, FAIStimulus Stimulus)
{
}

void UASAC_AISensesHandler::HandlePrediction(AActor* Actor, FAIStimulus Stimulus)
{
}


