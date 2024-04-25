// Fill out your copyright notice in the Description page of Project Settings.


#include "UWTabMenu.h"
#include "UWSettingsMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UUWTabMenu::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
	ResumeBtn->OnClicked.AddDynamic(this, &ThisClass::OnResumeClicked);
	MainMenuBtn->OnClicked.AddDynamic(this, &ThisClass::OnMainMenuClicked);
	SettingBtn->OnClicked.AddDynamic(this, &ThisClass::OnSettingClicked);
	SaveBtn->OnClicked.AddDynamic(this, &ThisClass::OnSaveClicked);
	QuitBtn->OnClicked.AddDynamic(this, &ThisClass::OnQuitClicked);

	SettingMenuWidget = Cast<UUWSettingsMenu>(CreateWidget<UUserWidget>(GetWorld(), SettingMenuClass)); // Create Widget
	if (!SettingMenuWidget)
		return;
	SettingMenuWidget->AddToViewport(); // Add it to the viewport so the Construct() method in the UUserWidget:: is run.
	SettingMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set it to hidden so its not open on spawn.
}

void UUWTabMenu::ToggleMenu()
{
	if (bShowingMenu)
		bShowingMenu = false;
	else
		bShowingMenu = true;

	APlayerController* PC = GetOwningPlayer();
	if (!PC)
		return;
	if (bShowingMenu)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		PC->SetInputMode(FInputModeUIOnly());
		SetKeyboardFocus();
		SetVisibility(ESlateVisibility::Visible);
	}
	else {
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
		PC->SetInputMode(FInputModeGameOnly());
		SetKeyboardFocus();
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUWTabMenu::OnResumeClicked()
{
	ToggleMenu();
}

void UUWTabMenu::OnMainMenuClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Return to Menu"));
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UUWTabMenu::OnSettingClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Settings"));
	SetVisibility(ESlateVisibility::Hidden);
	SettingMenuWidget->OpenMenu(this);
}

void UUWTabMenu::OnSaveClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save"));
}

void UUWTabMenu::OnQuitClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Quit"));
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
