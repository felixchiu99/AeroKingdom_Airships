// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASCharacterMimic.generated.h"

class UCameraComponent;
class AASMimicBase;
class AAeroKingdom_AirshipsCharacter;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASCharacterMimic : public AActor
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	AAeroKingdom_AirshipsCharacter* Character;

	APlayerController* Controller;

	AASMimicBase* MimicReference;

	AASMimicBase* RealReference;
	
public:	
	// Sets default values for this actor's properties
	AASCharacterMimic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CalculateViewpoint();

	void MimicTransform();

	void OnExitViewpoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetMimicCharacter(AAeroKingdom_AirshipsCharacter* parent);
	void UnsetMimicCharacter();

	void SetMimicView();
	void UnsetMimicView();

	void SetMimicReference(AASMimicBase* parent);
	void UnsetMimicReference();
	void SetRealReference(AASMimicBase* parent);

	void OnExit();
};
