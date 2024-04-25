// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWCommonSlider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCSUIOnChangedSignature, class UUWCommonSlider*, Slider, float, Value);


UCLASS()
class AEROKINGDOM_AIRSHIPS_API UUWCommonSlider : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SliderLabel;

	UPROPERTY(meta = (BindWidget))
	class USlider* MainSlider;

	UPROPERTY(meta = (BindWidget))
	class UButton* MinusBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlusBtn;

public:
	FCSUIOnChangedSignature OnChangedDelegate;

	float GetSliderValue();

	UFUNCTION()
	void OnSliderChanged(float fValue);

	UFUNCTION()
	void OnPlusClicked();

	UFUNCTION()
	void OnMinusClicked();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SliderLabel")
	FText SliderLabelText = NSLOCTEXT("CommonLabel", "LabelKey", "SliderText");

};
