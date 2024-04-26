// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Input/Reply.h"
#include "UWTabMenu.generated.h"

class UInputAction;

UCLASS(Abstract)
class AEROKINGDOM_AIRSHIPS_API UUWTabMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void ToggleMenu();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level|Config")
	FName LevelName = "MainMenu";

	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* SaveBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitBtn;

	/** Menu Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuAction;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnMainMenuClicked();

	UFUNCTION()
	void OnSettingClicked();
	
	UFUNCTION()
	void OnSaveClicked();

	UFUNCTION()
	void OnQuitClicked();

	bool IsKeyDown(FKey Pressed, UInputAction* RelatedAction);

	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UUWSettingsMenu> SettingMenuClass;

	class UUWSettingsMenu* SettingMenuWidget;

	bool bShowingMenu = false;
};
