// Fill out your copyright notice in the Description page of Project Settings.


#include "SeperatedLinearDamping.h"

// Sets default values for this component's properties
USeperatedLinearDamping::USeperatedLinearDamping()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USeperatedLinearDamping::BeginPlay()
{
	Super::BeginPlay();
	Actor = GetOwner();
	
}


// Called every frame
void USeperatedLinearDamping::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	
}

void USeperatedLinearDamping::ApplyDamping(float DeltaTime)
{
	FVector linearVelocity = Actor->GetVelocity();
	FVector linearDamping = FVector(0.5, 0.5, 0.1);

	FVector linearDampingTimesDeltaSeconds = linearDamping * DeltaTime;
	FVector linearVelocityMultiplier = FVector(
		FGenericPlatformMath::Max(0.0f, 1.0f - linearDampingTimesDeltaSeconds.X),
		FGenericPlatformMath::Max(0.0f, 1.0f - linearDampingTimesDeltaSeconds.Y),
		FGenericPlatformMath::Max(0.0f, 1.0f - linearDampingTimesDeltaSeconds.Z));
	linearVelocity *= linearVelocityMultiplier;
	if (Actor != nullptr)
	{
		USceneComponent* Component = Actor->GetRootComponent();
		if (Component != nullptr)
		{
			//Component->SetAllPhysicsLinearVelocity(NewVelocity, false);
		}
	}
}



