// Fill out your copyright notice in the Description page of Project Settings.


#include "UITestWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UUITestWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GenerateRandom();
	GenerateButton->OnClicked.AddUniqueDynamic(this, &UUITestWidget::OnClickedGenerateButton);
}

void UUITestWidget::GenerateRandom()
{
	int32 RandomNumber = FMath::RandRange(0, 100);
	RandomNumberLabel->SetText(FText::AsNumber(RandomNumber));
}

void UUITestWidget::OnClickedGenerateButton()
{
	GenerateRandom();
}
