// Fill out your copyright notice in the Description page of Project Settings.


#include "ASVehicle.h"

// Sets default values
AASVehicle::AASVehicle()
{
	PrimaryActorTick.bCanEverTick = true;
	Core = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Core"));
	Core->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/ Script / Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		Core->SetStaticMesh(Base.Object);
	}
}

void AASVehicle::BeginPlay()
{
	Super::BeginPlay();
}

void AASVehicle::MoveForward()
{
}

void AASVehicle::MoveBackward()
{
}

void AASVehicle::MoveLeft()
{
}

void AASVehicle::MoveRight()
{
}

void AASVehicle::MoveUp()
{
}

void AASVehicle::MoveDown()
{
}

void AASVehicle::YawLeft()
{
}

void AASVehicle::YawRight()
{
}

void AASVehicle::RollLeft()
{
}

void AASVehicle::RollRight()
{
}

void AASVehicle::PitchUp()
{
}

void AASVehicle::PitchDown()
{
}

void AASVehicle::AxisForward(float input)
{
}

void AASVehicle::AxisRight(float input)
{
}

void AASVehicle::AxisUp(float input)
{
}

void AASVehicle::Yaw(float input)
{
}

void AASVehicle::Roll(float input)
{
}

void AASVehicle::Pitch(float input)
{
}

