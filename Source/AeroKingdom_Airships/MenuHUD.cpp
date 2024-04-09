// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuHUD.h"
#include "Engine/Engine.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "LevelLoader.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	Loader = new LevelLoader();
	Loader->AddWorldContext(GetWorld());
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport) {
		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));

		if (PlayerOwner) 
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());
		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AMenuHUD::LoadLevel(FName levelName)
{
	RemoveMenu();
	Loader->LoadLevel(levelName);
}
