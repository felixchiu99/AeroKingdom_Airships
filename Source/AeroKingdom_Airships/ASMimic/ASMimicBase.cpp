// Fill out your copyright notice in the Description page of Project Settings.


#include "ASMimicBase.h"
#include "../AeroKingdom_AirshipsCharacter.h"
#include "Components/BoxComponent.h"
// Sets default values
AASMimicBase::AASMimicBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TempMesh"));
	SetRootComponent(TestMesh);

	Box = CreateDefaultSubobject<UBoxComponent>(FName("BoxMesh"));
	Box->SetupAttachment(RootComponent);
	//Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Box->SetGenerateOverlapEvents(true);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AASMimicBase::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AASMimicBase::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AASMimicBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASMimicBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("in"));
}

void AASMimicBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("out"));
}

// Called every frame
void AASMimicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AASMimicBase::GetRelativeLocation(FVector location)
{
	return location - this->GetActorLocation();
}



