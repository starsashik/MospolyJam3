// Fill out your copyright notice in the Description page of Project Settings.


#include "EPICCube.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"

// Sets default values
AEPICCube::AEPICCube():
	bPickUp(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	SetRootComponent(Cube);
	CheckCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckCollision"));
	CheckCollision->SetupAttachment(Cube);
}

// Called when the game starts or when spawned
void AEPICCube::BeginPlay()
{
	Super::BeginPlay();
	CheckCollision->OnComponentBeginOverlap.AddDynamic(this, &AEPICCube::BeginOver);
	CheckCollision->OnComponentEndOverlap.AddDynamic(this, &AEPICCube::EndOver);
	CheckCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AEPICCube::BeginOver(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (!bPickUp)
	//{
	//	auto Player = Cast<AMainCharacter>(OtherActor);
	//	if (Player)
	//	{
	//		Player->SetActorToInteract(this);
	//		ShowMyWidget(true);
	//	}
	//}
}

void AEPICCube::EndOver(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (!bPickUp)
	//{
	//	auto Player = Cast<AMainCharacter>(OtherActor);
	//	if (Player)
	//	{
	//		Player->SetActorToInteract(nullptr);
	//		ShowMyWidget(false);
	//	}
	//}
}

// Called every frame
void AEPICCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEPICCube::PickUp(bool condition)
{
	bPickUp = condition;
	if (condition)
	{
		Cube->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		Cube->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

