// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBall.h"
#include "Components/WidgetComponent.h"

// Sets default values
ARollingBall::ARollingBall( const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	Ball->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/ Script / Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		Ball->SetStaticMesh(Base.Object);
	}

	HealthWidgetComp = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("HealthBar"));
	HealthWidgetComp->AttachToComponent(Ball, FAttachmentTransformRules::KeepRelativeTransform);

	Health = MaxHealth;
}

// Called when the game starts or when spawned
void ARollingBall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARollingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

