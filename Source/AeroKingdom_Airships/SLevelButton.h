// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class AEROKINGDOM_AIRSHIPS_API SLevelButton : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SLevelButton) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)
	SLATE_ARGUMENT(FName, LevelName)

	SLATE_END_ARGS()

	FName LevelName = "AirshipTest";
	FString LevelNameTitle = "AirshipTestName";

	/* every widget needs a contruction function */
	void Construct(const FArguments& InArgs);

	FReply OnClicked() const;

	/** the HUD that Created This widget*/
	TWeakObjectPtr<class AMenuHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; }
};
