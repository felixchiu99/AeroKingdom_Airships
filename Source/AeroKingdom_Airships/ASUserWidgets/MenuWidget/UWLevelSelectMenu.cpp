// Fill out your copyright notice in the Description page of Project Settings.


#include "UWLevelSelectMenu.h"
#include "../ComponentWidget/UWCommonLevelLoadButton.h"

void UUWLevelSelectMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (AirshipBtn)
		AirshipBtn->OnClickedDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasClicked);
	if (WeaponBtn)
		WeaponBtn->OnClickedDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasClicked);
	if (UIBtn)
		UIBtn->OnClickedDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasClicked);
}

void UUWLevelSelectMenu::OnButtonWasClicked(UUWCommonLevelLoadButton* Button)
{
	Button->LoadLevel();
}
