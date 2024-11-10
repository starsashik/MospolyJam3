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
	bool bIsNewGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlreadyStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PlayerLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> LocationCheckPointMap1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> LocationCheckPointMap2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> LocationCheckPointMap3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IdCheckPointMap1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IdCheckPointMap2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IdCheckPointMap3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> Collectables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CompleteMap1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CompleteMap2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CompleteMap3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Upgrade;

	UFUNCTION(BlueprintCallable)
	void ClearForNewGame();
};
