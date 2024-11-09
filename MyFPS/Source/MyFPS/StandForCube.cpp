// Fill out your copyright notice in the Description page of Project Settings.


#include "StandForCube.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "EPICCube.h"

// Sets default values
AStandForCube::AStandForCube():
	NumberOfCube(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand"));
	SetRootComponent(Stand);
	CheckCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckCollision"));
	CheckCollision->SetupAttachment(Stand);

	ForCube0 = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube0"));
	ForCube0->SetupAttachment(RootComponent);
	ForCube1 = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube1"));
	ForCube1->SetupAttachment(RootComponent);
	ForCube2 = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube2"));
	ForCube2->SetupAttachment(RootComponent);
}

void AStandForCube::AttachCubeByRef(AEPICCube* cube)
{
	if (NumberOfCube < 3)
	{
		cube->SetActorScale3D(FVector(1.f, 1.f, 1.f));
		cube->PickUp(false);
		if (NumberOfCube == 0)
		{
			cube->AttachToComponent(ForCube0, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		else if (NumberOfCube == 1)
		{
			cube->AttachToComponent(ForCube1, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		else if (NumberOfCube == 2)
		{
			cube->AttachToComponent(ForCube2, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		InteractActors[NumberOfCube] = cube;
		NumberOfCube += 1;
	}
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("123123"));
	}
}

void AStandForCube::EndOver(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Player = Cast<AMainCharacter>(OtherActor);
	if (Player)
	{
		Player->SetNearStand(nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("123123"));
	}
}

// Called every frame
void AStandForCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

