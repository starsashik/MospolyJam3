// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeOnMap.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyMainSaveGame.h"

// Sets default values
AUpgradeOnMap::AUpgradeOnMap():
	Upgrade(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void AUpgradeOnMap::BeginPlay()
{
	Super::BeginPlay();
	UMyMainSaveGame* SaveInst = Cast<UMyMainSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MainSave"), 0));
	if (SaveInst->Upgrade != Upgrade)
	{
		Destroy();
	}
	
}

// Called every frame
void AUpgradeOnMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

