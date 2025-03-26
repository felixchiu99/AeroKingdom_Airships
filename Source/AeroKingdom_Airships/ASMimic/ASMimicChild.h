// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASMimicBase.h"
#include "ASMimicChild.generated.h"

class AASMimicParent;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASMimicChild : public AASMimicBase
{
	GENERATED_BODY()
	
	AASMimicParent* MimicParent;

	bool hasChar = false;
public:	
	// Sets default values for this actor's properties
	AASMimicChild();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void OnOverlapEndPlayer(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMimicParent(AASMimicParent* parent);

	bool HasChild() { return hasChar; }

	void SetHasChild(bool hasChar) override;
};
