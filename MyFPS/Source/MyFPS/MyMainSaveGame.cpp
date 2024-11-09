// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMainSaveGame.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/GameplayStatics.h"

UMyMainSaveGame::UMyMainSaveGame()
{
	Money = 0;
	PlayerLoc = FVector(0.f, 0.f, 0.f);
	PlayerRotation = FRotator(0.f, 0.f, 0.f);
	bIsNewGame = true;
	bAlreadyStart = false;
}

void UMyMainSaveGame::SaveBeforeQuit()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("SaveFunc"));
	UGameplayStatics::SaveGameToSlot(this, TEXT("MainSave"), 0);
}

void UMyMainSaveGame::ClearForNewGame()
{
	PlayerLoc = FVector(0.f, 0.f, 0.f);
	PlayerRotation = FRotator(0.f, 0.f, 0.f);
	Money = 0;
	UGameplayStatics::SaveGameToSlot(this, TEXT("MainSave"), 0);
}
