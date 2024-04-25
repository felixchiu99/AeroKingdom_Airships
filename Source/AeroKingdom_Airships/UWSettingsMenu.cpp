// Fill out your copyright notice in the Description page of Project Settings.


#include "UWSettingsMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "UWCommonSlider.h"
#include "GIAirshipGameInstance.h"

void UUWSettingsMenu::OpenMenu(UUserWidget* InMenu)
{
	SetPreviousMenu(InMenu);
	//SetVisibility(ESlateVisibility::Visible);
	APlayerController* PC = GetOwningPlayer();
	if (!PC)
		return;
	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;
	PC->SetInputMode(FInputModeUIOnly());
	SetVisibility(ESlateVisibility::Visible);
}

void UUWSettingsMenu::NativeConstruct()
{
	BackBtn->OnClicked.AddDynamic(this, &ThisClass::OnBackBtnClicked);

	MusicSlider->OnChangedDelegate.AddUniqueDynamic(this, &ThisClass::OnCommonSliderChanged);
	SFXSlider->OnChangedDelegate.AddUniqueDynamic(this, &ThisClass::OnCommonSliderChanged);
	AmbientSlider->OnChangedDelegate.AddUniqueDynamic(this, &ThisClass::OnCommonSliderChanged);
}

void UUWSettingsMenu::SetPreviousMenu(UUserWidget* InMenu)
{
	PreviousMenu = InMenu;
}

void UUWSettingsMenu::OnSliderChanged(float fValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Slider " + FString::SanitizeFloat(fValue)));

	Cast<UGIAirshipGameInstance>(GetGameInstance())->SetSFXVolume(fValue);
}

void UUWSettingsMenu::OnBackBtnClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Back "));
	SetVisibility(ESlateVisibility::Hidden);
	if (!PreviousMenu)
		return;
	PreviousMenu->AddToViewport();
	PreviousMenu->SetVisibility(ESlateVisibility::Visible);
}

void UUWSettingsMenu::OnCommonSliderChanged(UUWCommonSlider* Slider , float Value)
{
	if (Slider == MusicSlider) {
		Cast<UGIAirshipGameInstance>(GetGameInstance())->SetMusicVolume(Value);
	}

	if (Slider == SFXSlider) {
		Cast<UGIAirshipGameInstance>(GetGameInstance())->SetSFXVolume(Value);
	}

	if (Slider == AmbientSlider) {
		Cast<UGIAirshipGameInstance>(GetGameInstance())->SetAmbientVolume(Value);
	}
}
