// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ASIInteractableInterface.h"
#include "ASInteractablePawn.generated.h"

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASInteractablePawn : public APawn, public IASIInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AASInteractablePawn();

	FVector GetTooltipDisplayPoint() override;
	bool HasTooltipDisplayPoint() override;
	FText GetTooltipDisplayName() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tooltip")
	FText TooltipLabelText = NSLOCTEXT("Tooltip", "ActionLabel", "Press");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI|Tooltip")
	class UArrowComponent* TooltipDisplayPoint;
};
