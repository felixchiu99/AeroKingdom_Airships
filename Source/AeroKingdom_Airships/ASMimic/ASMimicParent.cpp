// Fill out your copyright notice in the Description page of Project Settings.

//the ship you walk into

#include "ASMimicParent.h"
#include "ASMimicChild.h"
#include "ASCharacterMimic.h"
#include "../AeroKingdom_AirshipsCharacter.h"

// Sets default values
AASMimicParent::AASMimicParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AASMimicParent::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* const World = GetWorld();
	FTransform SpawnPointVector;
	SpawnPointVector.SetLocation(FVector(3000.0, 6000, 210.0));

	FActorSpawnParameters ActorSpawnParams;
	if (World != nullptr)
	{
		MimicChild = World->SpawnActor<AASMimicChild>(MimicChildClass, SpawnPointVector, ActorSpawnParams);
		MimicChild->SetMimicParent(this);
		MimicCharacter = World->SpawnActor<AASCharacterMimic>(CharacterMimicClass, SpawnPointVector, ActorSpawnParams);
	}


}

void AASMimicParent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlapBeginPlayer(OtherActor);
}

void AASMimicParent::OnOverlapBeginPlayer(AActor* OtherActor)
{
	if (MimicChild->HasChild())
		return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("in Parent"));
	AAeroKingdom_AirshipsCharacter* player = Cast<AAeroKingdom_AirshipsCharacter>(OtherActor);
	if (player) {
		FVector relativePosition = player->GetActorLocation() - this->GetActorLocation();
		player->SetActorLocation(MimicChild->GetActorLocation() + relativePosition);
		MimicCharacter->SetMimicCharacter(player);
		MimicCharacter->SetMimicView();
		MimicCharacter->SetMimicReference(MimicChild);
		MimicCharacter->SetRealReference(this);
	}
}



// Called every frame
void AASMimicParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASMimicParent::ChildExcaped()
{
	MimicCharacter->OnExit();
}

