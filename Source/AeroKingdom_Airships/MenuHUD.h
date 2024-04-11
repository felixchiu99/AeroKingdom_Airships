// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class LevelLoader;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	
	LevelLoader* Loader;

public:
	enum MenuName 
	{
		Main,
		LevelSelect,
		Pause,
		Setting
	};

protected:
	TSharedPtr<class SMainMenuWidget> MainMenuWidget;
	TSharedPtr<class SLevelSelectMenuWidget> LevelSelectMenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;

	void ShowMainMenu();
	void ShowLevelSelectMenu();
	void ShowSelectedMenu(enum MenuName name);

public:
	void ShowMenu(enum MenuName name = MenuName::Main);
	void RemoveMenu();
	void LoadLevel(FName levelName);
};
