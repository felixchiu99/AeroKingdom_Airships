// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASMimicBase.generated.h"

class UBoxComponent;
class AAeroKingdom_AirshipsCharacter;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASMimicBase : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* TestMesh;

	UPROPERTY(VisibleDefaultsOnly)
	class AAeroKingdom_AirshipsCharacter* Temp;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* Box;
public:	
	// Sets default values for this actor's properties
	AASMimicBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetRelativeLocation(FVector location);

	virtual void SetHasChild(bool hasChar) {};

};
