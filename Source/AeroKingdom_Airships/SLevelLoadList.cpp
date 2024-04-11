// Fill out your copyright notice in the Description page of Project Settings.


#include "SLevelLoadList.h"
#include "SLevelButton.h"

void SLevelLoadList::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;

	MapNames.Add("WeaponLevel", "WeaponsTest");
	MapNames.Add("AirshipLevel", "AirshipTest");
	MapNames.Add("UILevel", "UI_Test");

	TSharedPtr<SVerticalBox> Container = SNew(SVerticalBox);

	const FMargin ButtonPadding = FMargin(10.f);

	for (auto It = MapNames.CreateConstIterator(); It; ++It)
	{
		Container->AddSlot().Padding(ButtonPadding)
			[
				SNew(SLevelButton)
					.OwningHUD(OwningHUD)
					.LevelNameTitle(It.Key())
					.LevelName(*It.Value())
			];
	}

	ChildSlot
		[
			Container.ToSharedRef()
		];
}
