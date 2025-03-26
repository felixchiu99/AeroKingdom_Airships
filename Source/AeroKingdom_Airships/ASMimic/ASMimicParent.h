// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASMimicBase.h"
#include "ASMimicParent.generated.h"

class AASMimicChild;
class AAeroKingdom_AirshipsCharacter;
class AASCharacterMimic;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASMimicParent : public AASMimicBase
{
	GENERATED_BODY()

	/** ASMimicChild class to spawn */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AASMimicChild> MimicChildClass;

	AASMimicChild* MimicChild;

	/** AASCharactorMimic class to spawn */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AASCharacterMimic> CharacterMimicClass;

	AASCharacterMimic* MimicCharacter;
	
public:	
	// Sets default values for this actor's properties
	AASMimicParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	void OnOverlapBeginPlayer(AActor* OtherActor);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChildExcaped();
};
