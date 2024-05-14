// Fill out your copyright notice in the Description page of Project Settings.


#include "ASA_Target.h"
#include "../ASComponents/ASAC_WaypointComponent.h"
#include "../ASTest/ASA_WaypointActor.h"

// Sets default values
AASA_Target::AASA_Target()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	TargetMesh->SetupAttachment(GetRootComponent());

	WaypointComponent = CreateDefaultSubobject<UASAC_WaypointComponent>(TEXT("WaypointComponment"));
}

// Called when the game starts or when spawned
void AASA_Target::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASA_Target::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToWaypoint();
}

void AASA_Target::SetWaypointComponent(UASAC_WaypointComponent* WPComponent)
{
	WaypointComponent->SetWaypoints(WPComponent->GetWaypoints());
}

void AASA_Target::MoveToWaypoint()
{
	SetActorLocation(FMath::Lerp(GetActorLocation(), WaypointComponent->GetWaypointLocation(), GetWorld()->GetDeltaSeconds() * MoveSpeed));
	CheckArrivedWaypoint();
}

void AASA_Target::CheckArrivedWaypoint()
{
	if (FVector::Dist(GetActorLocation() , WaypointComponent->GetWaypointLocation()) < 10.f) {
		WaypointComponent->NextIndex();
	}
}

