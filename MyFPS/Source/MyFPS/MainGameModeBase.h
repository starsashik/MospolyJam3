// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYFPS_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainGameModeBase();

	UFUNCTION(BlueprintCallable)
	void MyPauseGame(int change);

private:
	FString NameMainSave;
	int NumberPause;
};
