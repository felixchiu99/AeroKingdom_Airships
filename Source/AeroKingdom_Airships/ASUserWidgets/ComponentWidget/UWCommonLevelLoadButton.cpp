// Fill out your copyright notice in the Description page of Project Settings.


#include "UWCommonLevelLoadButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "LevelButton"

void UUWCommonLevelLoadButton::NativeConstruct()
{
	Super::NativeConstruct();

	MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClicked);

	if (MainButtonLabel)
		MainButtonLabel->SetText(FText::FromName(LevelName));
}

void UUWCommonLevelLoadButton::OnButtonClicked()
{
	OnClickedDelegate.Broadcast(this);
}

void UUWCommonLevelLoadButton::LoadLevel()
{
	if (GetWorld()) {
		
		APlayerController* PC = GetOwningPlayer();

		if (PC)
		{
			PC->bShowMouseCursor = false;
			PC->bEnableClickEvents = false;
			PC->bEnableMouseOverEvents = false;
			PC->SetInputMode(FInputModeGameOnly());
		}

		UGameplayStatics::OpenLevel(GetWorld(), LevelName);


	}
}

#undef LOCTEXT_NAMESPACE