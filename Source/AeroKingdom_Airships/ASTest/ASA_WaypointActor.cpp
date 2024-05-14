// Fill out your copyright notice in the Description page of Project Settings.


#include "ASA_WaypointActor.h"

// Sets default values
AASA_WaypointActor::AASA_WaypointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AASA_WaypointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASA_WaypointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

