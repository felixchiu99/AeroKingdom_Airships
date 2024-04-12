// Fill out your copyright notice in the Description page of Project Settings.


#include "SLevelLoadList.h"
#include "SLevelButton.h"
#include "Engine/ObjectLibrary.h"

void SLevelLoadList::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;

	TArray<FString> LvlNames = GetFolderName("/Game/FirstPerson/Maps/Maps");
	TSharedPtr<SVerticalBox> Container = SNew(SVerticalBox);

	const FMargin ButtonPadding = FMargin(10.f);

	for (auto& LvlName : LvlNames)
	{
		Container->AddSlot().Padding(ButtonPadding)
			[
				SNew(SLevelButton)
					.OwningHUD(OwningHUD)
					.LevelName(FName(*LvlName))
			];
	}

	ChildSlot
		[
			Container.ToSharedRef()
		];
}

TArray<FString> SLevelLoadList::GetFolderName(FString MapPath)
{
	auto ObjectLibrary = UObjectLibrary::CreateLibrary(UWorld::StaticClass(), false, true);
	ObjectLibrary->LoadAssetDataFromPath(MapPath);
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);

	TArray<FString> Names = TArray<FString>();

	for (int32 i = 0; i < AssetDatas.Num(); ++i)
	{
		FAssetData& AssetData = AssetDatas[i];

		auto name = AssetData.AssetName.ToString();

		Names.Add(name);
	}

	return Names;
}
