// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
/**
 * 
 */
class AEROKINGDOM_AIRSHIPS_API SLevelLoadList : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SLevelLoadList) {}

		SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)

	SLATE_END_ARGS()

	/* every widget needs a contruction function */
	void Construct(const FArguments& InArgs);

	TArray<FString> GetFolderName(FString MapPath);

	/** the HUD that Created This widget*/
	TWeakObjectPtr<class AMenuHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; }
};
