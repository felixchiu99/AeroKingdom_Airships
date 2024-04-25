// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWSettingsMenu.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UUWSettingsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI|Menu")
	void OpenMenu(UUserWidget* InMenu);

protected:
	virtual void NativeConstruct() override;

	void SetPreviousMenu(UUserWidget* InMenu);

	UFUNCTION()
	void OnSliderChanged(float fValue);

	UFUNCTION()
	void OnBackBtnClicked();

	UFUNCTION()
	void OnCommonSliderChanged(UUWCommonSlider* Slider, float Value);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MenuTitle;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackBtn;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SoundTitle;

	UPROPERTY(meta = (BindWidget))
	class UUWCommonSlider* MusicSlider;

	UPROPERTY(meta = (BindWidget))
	class UUWCommonSlider* SFXSlider;

	UPROPERTY(meta = (BindWidget))
	class UUWCommonSlider* AmbientSlider;

	UPROPERTY()
	class UUserWidget* PreviousMenu;
};
