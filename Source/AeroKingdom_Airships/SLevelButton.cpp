// Fill out your copyright notice in the Description page of Project Settings.

#include "SLevelButton.h"
#include "MenuHUD.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "LevelButton"

void SLevelButton::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.f);

	const FText ButtonText = LOCTEXT("ButtonText", "test1");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	ChildSlot
		[

			SNew(SButton)
				.OnClicked(this, &SLevelButton::OnClicked)
				[
					SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(ButtonText)
						.Justification(ETextJustify::Center)
				]
		];
}

FReply SLevelButton::OnClicked() const
{
	if (OwningHUD.IsValid()) {
		OwningHUD->LoadLevel(LevelName);
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
