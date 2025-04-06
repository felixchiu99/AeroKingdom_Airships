// Fill out your copyright notice in the Description page of Project Settings.

//the ship you walk on

#include "ASMimicChild.h"
#include "ASMimicParent.h"
#include "../AeroKingdom_AirshipsCharacter.h"

// Sets default values
AASMimicChild::AASMimicChild()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AASMimicChild::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASMimicChild::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("in child"));
}

void AASMimicChild::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnOverlapEndPlayer(OtherActor);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("out child"));
	//MimicParent->ChildExcaped();
}

void AASMimicChild::OnOverlapEndPlayer(AActor* OtherActor)
{
	AAeroKingdom_AirshipsCharacter* player = Cast<AAeroKingdom_AirshipsCharacter>(OtherActor);
	if (player) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("out child player"));
		// FVector relativePosition = player->GetActorLocation() - this->GetActorLocation();
		// player->SetActorLocation(MimicParent->GetActorLocation() + relativePosition);
		MimicParent->ChildExcaped();
	}
}

// Called every frame
void AASMimicChild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASMimicChild::SetMimicParent(AASMimicParent* parent)
{
	MimicParent = parent;
}

void AASMimicChild::SetHasChild(bool newHasChar)
{
	this->hasChar = newHasChar;
}
