// Fill out your copyright notice in the Description page of Project Settings.

#include "SLevelButton.h"
#include "MenuHUD.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "LevelButton"

void SLevelButton::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;
	if (!InArgs._LevelName.IsNone())
		LevelName = InArgs._LevelName;

	//const FText ButtonText = LOCTEXT("LevelText", FText::FromString(LevelNameText));
	const FText ButtonText = FText::Format(LOCTEXT("LevelNameTitle {0}", "{1}"), FText::FromName(LevelName), FText::FromName(LevelName));

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
		OwningHUD->RemoveMenu();
		OwningHUD->LoadLevel(LevelName);
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
