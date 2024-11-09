// Fill out your copyright notice in the Description page of Project Settings.
#include "MainGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyMainSaveGame.h"

AMainGameModeBase::AMainGameModeBase():
	NameMainSave(TEXT("MainSave")),
	NumberPause(0)
{
	if (!UGameplayStatics::DoesSaveGameExist(NameMainSave, 0))
	{
		UMyMainSaveGame* SaveInst = Cast<UMyMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMyMainSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(SaveInst, NameMainSave, 0);
	}


}

void AMainGameModeBase::MyPauseGame(int change)
{
	NumberPause += change;
	if (NumberPause == 0 && change < 0)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false;
		}
	}
	else if (NumberPause == 1 && change > 0)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}
