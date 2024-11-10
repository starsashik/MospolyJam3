// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMainSaveGame.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/GameplayStatics.h"

UMyMainSaveGame::UMyMainSaveGame()
{
	PlayerLoc = FVector(0.f, 0.f, 0.f);
	bAlreadyStart = false;

	IdCheckPointMap1 = 0;
	IdCheckPointMap2 = 0;
	IdCheckPointMap3 = 0;

	CompleteMap1 = false;
	CompleteMap2 = false;
	CompleteMap3 = false;

	LocationCheckPointMap1 = { FVector(650.f,-430.f,362.f), FVector(670.f,-170.f,150.f), FVector(-600.f,-370.f,150.f) };
	LocationCheckPointMap2 = { FVector(0.f,0.f,120.f) };
	LocationCheckPointMap3 = { FVector(0.f,0.f,120.f) };

	Collectables.Init(false, 10);
	Upgrade = 0;

	CurrentMap = 0;
}


void UMyMainSaveGame::ClearForNewGame()
{
	PlayerLoc = FVector(0.f, 0.f, 0.f);

	IdCheckPointMap1 = 0;
	IdCheckPointMap2 = 0;
	IdCheckPointMap3 = 0;

	CompleteMap1 = false;
	CompleteMap2 = false;
	CompleteMap3 = false;

	Collectables.Init(false, 10);
	Upgrade = 0;
	CurrentMap = 0;

	UGameplayStatics::SaveGameToSlot(this, TEXT("MainSave"), 0);
}
