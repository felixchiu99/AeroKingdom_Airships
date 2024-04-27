// Fill out your copyright notice in the Description page of Project Settings.


#include "UWCommonSlider.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"

void UUWCommonSlider::NativeConstruct()
{
	MainSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnSliderChanged);
	PlusBtn->OnClicked.AddDynamic(this, &ThisClass::OnPlusClicked);
	MinusBtn->OnClicked.AddDynamic(this, &ThisClass::OnMinusClicked);


	if (SliderLabel)
		SliderLabel->SetText(SliderLabelText);
}

float UUWCommonSlider::GetSliderValue()
{
	return MainSlider->GetValue();
}

void UUWCommonSlider::OnSliderChanged(float fValue)
{
	OnChangedDelegate.Broadcast(this, fValue);
}

void UUWCommonSlider::OnPlusClicked()
{
	MainSlider->SetValue(MainSlider->GetValue() + MainSlider->GetStepSize());
}

void UUWCommonSlider::OnMinusClicked()
{
	MainSlider->SetValue(MainSlider->GetValue() - MainSlider->GetStepSize());
}
