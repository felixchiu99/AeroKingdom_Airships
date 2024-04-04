// Fill out your copyright notice in the Description page of Project Settings.


#include "AirshipPropulsion.h"

// Sets default values
AAirshipPropulsion::AAirshipPropulsion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EngineCore = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EngineCoreMesh"));
	EngineCore->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/ Script / Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		EngineCore->SetStaticMesh(Base.Object);
	}
}

void AAirshipPropulsion::ApplyThrust()
{
	EngineCore->AddForce(FVector(fThrustForce, 0, 0));
}




