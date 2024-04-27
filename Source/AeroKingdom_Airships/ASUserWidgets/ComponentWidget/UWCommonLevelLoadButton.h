// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWCommonLevelLoadButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCLLUIOnClickedSignature, class UUWCommonLevelLoadButton*, Button);


UCLASS()
class AEROKINGDOM_AIRSHIPS_API UUWCommonLevelLoadButton : public UUserWidget
{
	GENERATED_BODY()

public:
	FCLLUIOnClickedSignature OnClickedDelegate;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MainButtonLabel;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainButton;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level|Config")
	FName LevelName = "AirshipTest";

	UFUNCTION()
	void OnButtonClicked();

	void LoadLevel();
};
