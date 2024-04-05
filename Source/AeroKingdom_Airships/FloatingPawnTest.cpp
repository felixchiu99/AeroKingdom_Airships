// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPawnTest.h"
#include "AirshipController.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AFloatingPawnTest::AFloatingPawnTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Airship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AirshipMesh"));
	Airship->SetupAttachment(GetRootComponent());

	Balloon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMesh"));
	Balloon->SetupAttachment(Airship);

	ShipBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	//ShipBase->SetRelativeScale3D(FVector(8.f, 8.f, 0.1f));
	ShipBase->SetupAttachment(Airship);
	ShipBase->SetMassOverrideInKg("ShipBase", 10000.f, true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/ Script / Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		ShipBase->SetStaticMesh(Base.Object);
		Balloon->SetStaticMesh(Base.Object);
		Balloon->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	}

	//create a cannon sub actor
	AirshipController = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("AirshipController"));
	AirshipController->SetChildActorClass(ACAttachmentType);
	AirshipController->SetupAttachment(ShipBase);
	AirshipController->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	//Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating pawn movement"));
}

// Called when the game starts or when spawned
void AFloatingPawnTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingPawnTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloatingPawnTest::MoveForward()
{
}

void AFloatingPawnTest::MoveBackward()
{
}

