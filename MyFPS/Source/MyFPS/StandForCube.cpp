// Fill out your copyright notice in the Description page of Project Settings.


#include "StandForCube.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "EPICCube.h"

// Sets default values
AStandForCube::AStandForCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand"));
	SetRootComponent(Stand);
	CheckCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckCollision"));
	CheckCollision->SetupAttachment(Stand);

	ForCube = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube0"));
	ForCube->SetupAttachment(RootComponent);
}

void AStandForCube::AttachCubeByRef(AEPICCube* cube)
{
	cube->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));
	cube->PickUp(true);
	cube->AttachToComponent(ForCube, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	InteractActor = cube;
}


// Called when the game starts or when spawned
void AStandForCube::BeginPlay()
{
	Super::BeginPlay();
	CheckCollision->OnComponentBeginOverlap.AddDynamic(this, &AStandForCube::BeginOver);
	CheckCollision->OnComponentEndOverlap.AddDynamic(this, &AStandForCube::EndOver);
	CheckCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AStandForCube::BeginOver(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<AMainCharacter>(OtherActor);
	if (Player)
	{
		Player->SetNearStand(this);
		ShowMyWidget(true);
	}
}

void AStandForCube::EndOver(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Player = Cast<AMainCharacter>(OtherActor);
	if (Player)
	{
		Player->SetNearStand(nullptr);
		ShowMyWidget(false);
	}
}

// Called every frame
void AStandForCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

