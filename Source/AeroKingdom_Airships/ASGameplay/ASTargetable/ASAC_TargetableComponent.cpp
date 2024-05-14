// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAC_TargetableComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values for this component's properties
UASAC_TargetableComponent::UASAC_TargetableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UASAC_TargetableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* ParentActor = GetOwner();

	UAIPerceptionStimuliSourceComponent* SensorComponent = NewObject<UAIPerceptionStimuliSourceComponent>(ParentActor, TEXT("SenseSource"));
	ParentActor->AddInstanceComponent(SensorComponent);
	SensorComponent->RegisterComponent();
	SensorComponent->RegisterForSense(UAISense_Sight::StaticClass());
	SensorComponent->RegisterWithPerceptionSystem();
	ParentActor->Modify();

}


// Called every frame
void UASAC_TargetableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UASAC_TargetableComponent::GetLocation()
{
	return GetOwner()->GetActorLocation();
	//return GetOwner()->GetTargetLocation();
}

