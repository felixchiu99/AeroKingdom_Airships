// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuHUD.h"
#include "Engine/Engine.h"
#include "SMainMenuWidget.h"
#include "SLevelSelectMenuWidget.h"
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

void AMenuHUD::ShowMainMenu()
{
	MainMenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MainMenuWidget.ToSharedRef()));
}

void AMenuHUD::ShowLevelSelectMenu()
{
	LevelSelectMenuWidget = SNew(SLevelSelectMenuWidget).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(LevelSelectMenuWidget.ToSharedRef()));
}

void AMenuHUD::ShowSelectedMenu(enum MenuName name)
{
	switch (name)
	{
	case MenuName::LevelSelect:
		ShowLevelSelectMenu();
		break;
	case MenuName::Setting:
		ShowMainMenu();
		break;
	case MenuName::Pause:
		ShowMainMenu();
		break;
	case MenuName::Main:
	default:
		ShowMainMenu();
		break;
	}
}

void AMenuHUD::ShowMenu(enum MenuName name)
{

	if (GEngine && GEngine->GameViewport) {
		ShowSelectedMenu(name);

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
