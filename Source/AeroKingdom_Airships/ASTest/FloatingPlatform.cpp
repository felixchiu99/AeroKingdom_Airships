// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Airship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AirshipMesh"));
	Airship->SetupAttachment(GetRootComponent());
	Airship->SetSimulatePhysics(true);

	BalloonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMesh"));
	BalloonMesh->SetupAttachment(Airship);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	//BaseMesh->SetRelativeScale3D(FVector(8.f, 8.f, 0.1f));
	BaseMesh->SetupAttachment(Airship);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/ Script / Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		Airship->SetStaticMesh(Base.Object);
		BaseMesh->SetStaticMesh(Base.Object);
		BalloonMesh->SetStaticMesh(Base.Object);
		BalloonMesh->SetRelativeLocation(FVector(0.f, 0.f, 1000.0f));
	}
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	ToggleMovementDirection();

	/*
	if (!Airship) return;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FBodyInstance* BodyInst = Airship->GetBodyInstance();

	fMass
	*/
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ApplyLift(DeltaTime);

	MovePlatform();
	//MoveForward();
}

void AFloatingPlatform::AsyncPhysicsTickActor(float DeltaTime, float SimTime)
{
	//ApplyLift(DeltaTime);
	Super::AsyncPhysicsTickActor(DeltaTime, SimTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Physics!"));
}

void AFloatingPlatform::ApplyLift(float DeltaTime)
{
	/*
	if (GetVelocity().Z < 0) {
		BalloonMesh->AddImpulse(FVector(0, 0, -GetVelocity().Z*3), "None", true);
	}
	*/
	//BalloonMesh->AddForce(FVector(0, 0, 9.8f * 100), "None", true);
	DrawDebugLine(GetWorld(), BalloonMesh->GetComponentLocation(), BalloonMesh->GetComponentLocation() + FVector(0,0,100.f), FColor::Red, false, 0.1f, ECC_WorldStatic, 1.f);
	//Airship->AddImpulse(FVector(0, 0, 9.81f));
	Airship->AddForceAtLocation(FVector(0, 0, 9.80f * 100 * Airship->GetMass()), BalloonMesh->GetComponentLocation());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(Airship->GetMass()));
	DrawDebugLine(GetWorld(), Airship->GetCenterOfMass(), Airship->GetCenterOfMass() + FVector(0, 0, -100.f), FColor::Blue, false, 0.1f, ECC_WorldStatic, 1.f);
}

void AFloatingPlatform::MovePlatform()
{
	if (bIsForward) {
		MoveForward();
	}
	else {
		MoveBackward();
	}
}

void AFloatingPlatform::MoveForward()
{
	///*
	FVector location = GetActorLocation();
	location.X += fStep;
	SetActorRelativeLocation(location,true);
	//*/
	//BaseMesh->AddForce(FVector(10000 ,0,0));
}

void AFloatingPlatform::MoveBackward()
{
	FVector location = GetActorLocation();
	location.X -= fStep;
	SetActorRelativeLocation(location ,true);
}

void AFloatingPlatform::ToggleMovementDirection()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Set Fire Timer
		World->GetTimerManager().SetTimer(MoveTimer, this, &AFloatingPlatform::ToggleMovementDirection, 10.f, false);
		bIsForward = !bIsForward;
	}
}

