// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

// Sets default values
AVehicle::AVehicle()
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

void AVehicle::BeginPlay()
{
	Super::BeginPlay();
}

void AVehicle::MoveForward()
{
}

void AVehicle::MoveBackward()
{
}

void AVehicle::MoveLeft()
{
}

void AVehicle::MoveRight()
{
}

void AVehicle::MoveUp()
{
}

void AVehicle::MoveDown()
{
}

void AVehicle::YawLeft()
{
}

void AVehicle::YawRight()
{
}

void AVehicle::RollLeft()
{
}

void AVehicle::RollRight()
{
}

void AVehicle::PitchUp()
{
}

void AVehicle::PitchDown()
{
}

void AVehicle::AxisForward(float input)
{
}

void AVehicle::AxisRight(float input)
{
}

void AVehicle::AxisUp(float input)
{
}

void AVehicle::Yaw(float input)
{
}

void AVehicle::Roll(float input)
{
}

void AVehicle::Pitch(float input)
{
}

