// Fill out your copyright notice in the Description page of Project Settings.


#include "HighlightImprovements.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "MyMainSaveGame.h"

// Sets default values
AHighlightImprovements::AHighlightImprovements():
	Upgrade(0),
	Power(50),
	bWaveToFinish(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AHighlightImprovements::BeginPlay()
{
	Super::BeginPlay();
	if (MaterialClass != nullptr)
	{
		MyMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), MaterialClass);
		MyMaterial->SetVectorParameterValue("Color", Color);
		MyMaterial->SetScalarParameterValue("Power", 2.f);
		Mesh->SetMaterial(0, MyMaterial);
	}
	if (!bWaveToFinish)
	{
		UMyMainSaveGame* SaveInst = Cast<UMyMainSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MainSave"), 0));
		if (SaveInst->Upgrade == Upgrade || SaveInst->CurrentMap == Upgrade)
		{
			MyMaterial->SetScalarParameterValue("Power", Power);
		}
	}
	else
	{
		UMyMainSaveGame* SaveInst = Cast<UMyMainSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MainSave"), 0));
		if (!SaveInst->Collectables.Contains(false))
		{
			MyMaterial->SetScalarParameterValue("Power", Power);
		}
	}
}

// Called every frame
void AHighlightImprovements::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

