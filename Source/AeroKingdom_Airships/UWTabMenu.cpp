// Fill out your copyright notice in the Description page of Project Settings.


#include "UWTabMenu.h"
#include "UWSettingsMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"

void UUWTabMenu::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);

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

FReply UUWTabMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Key pressed " + InKeyEvent.GetKey().GetDisplayName().ToString()));
	
	if (IsKeyDown(InKeyEvent.GetKey(), MenuAction)) {
		OnResumeClicked();
	}

	return FReply::Handled();
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

bool UUWTabMenu::IsKeyDown(FKey Pressed, UInputAction* RelatedAction)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			auto keys = Subsystem->QueryKeysMappedToAction(RelatedAction);
			if (!keys.IsEmpty()) {
				return keys.Find(Pressed) != INDEX_NONE;
			}
		}
	}
	return false;
}
