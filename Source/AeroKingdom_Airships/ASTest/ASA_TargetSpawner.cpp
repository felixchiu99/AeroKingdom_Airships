// Fill out your copyright notice in the Description page of Project Settings.

#include "ASA_TargetSpawner.h"
#include "../ASDamageable/ASA_Target.h"
#include "../ASComponents/ASAC_WaypointComponent.h"

// Sets default values
AASA_TargetSpawner::AASA_TargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	SpawnerMesh->SetupAttachment(GetRootComponent());
	SpawnerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WaypointComponent = CreateDefaultSubobject<UASAC_WaypointComponent>(TEXT("TargetMesh"));
}

void AASA_TargetSpawner::SpawnTarget()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		//Spawn at root
		AASA_Target* target = World->SpawnActor<AASA_Target>(TargetClass, SpawnerMesh->GetComponentTransform(), ActorSpawnParams);
		target->SetWaypointComponent(WaypointComponent);

	}
}

// Called when the game starts or when spawned
void AASA_TargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnTarget();
}

// Called every frame
void AASA_TargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

