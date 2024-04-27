// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWLevelSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UUWLevelSelectMenu : public UUserWidget
{
	GENERATED_BODY()
	


	UPROPERTY(meta = (BindWidget))
	class UUWCommonLevelLoadButton* AirshipBtn;

	UPROPERTY(meta = (BindWidget))
	class UUWCommonLevelLoadButton* WeaponBtn;

	UPROPERTY(meta = (BindWidget))
	class UUWCommonLevelLoadButton* UIBtn;

	UPROPERTY(meta = (BindWidget))
	TArray<UUWCommonLevelLoadButton*> TestBtns;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonWasClicked(class UUWCommonLevelLoadButton* Button);
};
