// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "IToolTipInterface.h"
#include "WidgetTooltips.generated.h"

/**
 * 
 */
UCLASS(abstract)
class AEROKINGDOM_AIRSHIPS_API UWidgetTooltips : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetKeyName(FString name);

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* KeyBindName;


};
