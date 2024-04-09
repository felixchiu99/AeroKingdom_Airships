// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoader.h"
#include "Kismet/GameplayStatics.h"

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::AddWorldContext(UObject* Context)
{
    WorldContext = Context;
}

void LevelLoader::LoadLevel(FName LevelName)
{
    if (WorldContext) {
        FLatentActionInfo LatentInfo;
        UGameplayStatics::OpenLevel(WorldContext, LevelName);
    }
    
}
