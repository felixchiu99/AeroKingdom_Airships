// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UITestWidget.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UUITestWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void GenerateRandom();

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* RandomNumberLabel;

	UPROPERTY(meta = (BindWidget))
		class UButton* GenerateButton;

	UFUNCTION()
		void OnClickedGenerateButton();

		void NativeConstruct() override;
};
