// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyMainSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYFPS_API UMyMainSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UMyMainSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNewGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlreadyStart;

	FVector PlayerLoc;
	FRotator PlayerRotation;

	UFUNCTION(BlueprintCallable)
	void SaveBeforeQuit();

	UFUNCTION(BlueprintCallable)
	void ClearForNewGame();
};
