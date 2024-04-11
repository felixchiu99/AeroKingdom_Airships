// Fill out your copyright notice in the Description page of Project Settings.


#include "SLevelSelectMenuWidget.h"
#include "MenuHUD.h"
#include "SLevelLoadList.h"
#include "SLevelButton.h"

#define LOCTEXT_NAMESPACE "LevelSelectMenu"

void SLevelSelectMenuWidget::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.f);

	const FText TitleText = LOCTEXT("LevelSelectMenuTitle", "Level Select");
	const FText BackText = LOCTEXT("BackGame", "Back");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	ChildSlot
		[

			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.ColorAndOpacity(FColor::Black)
				]
				//Contents Text
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(ContentPadding)
				[
					SNew(SVerticalBox)
						// Levels
						+ SVerticalBox::Slot()
						[
							SNew(SLevelLoadList).OwningHUD(OwningHUD)
						]
						
						// Back button
						+ SVerticalBox::Slot()
						[
							SNew(SButton)
								.OnClicked(this, &SLevelSelectMenuWidget::OnBackClicked)
								[
									SNew(STextBlock)
										.Font(ButtonTextStyle)
										.Text(BackText)
										.Justification(ETextJustify::Center)
								]
						]
				]
		];

}

FReply SLevelSelectMenuWidget::OnBackClicked() const
{
	if (OwningHUD.IsValid()) {
		OwningHUD->RemoveMenu();
		OwningHUD->ShowMenu(AMenuHUD::MenuName::Main);
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE