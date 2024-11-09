// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadlySpikes.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"

// Sets default values
ADeadlySpikes::ADeadlySpikes() :
	bIsFly(false),
	FlyTime(2.f),
	PauseTime(5.f),
	FlySpeed(20.f),
	bFlyDown(false),
	bIsEnabled(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	Spikes = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spikes"));
	Spikes->SetupAttachment(SceneComponent);

	SpikeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SpikeCollision"));
	SpikeCollision->SetupAttachment(Spikes);
}

void ADeadlySpikes::Fly()
{
	bIsFly = true;
	bFlyDown = !bFlyDown;
	GetWorldTimerManager().ClearTimer(BeforeFlyDownTimer);
	GetWorldTimerManager().SetTimer(BeforeFlyDownTimer, this, &ADeadlySpikes::PauseBeforeFlyDown, FlyTime);
}

void ADeadlySpikes::PauseBeforeFlyDown()
{
	bIsFly = false;
	GetWorldTimerManager().ClearTimer(FlyDownTimer);
	GetWorldTimerManager().SetTimer(FlyDownTimer, this, &ADeadlySpikes::Fly, PauseTime);
}
// Called when the game starts or when spawned
void ADeadlySpikes::BeginPlay()
{
	Super::BeginPlay();
	SpikeCollision->OnComponentBeginOverlap.AddDynamic(this, &ADeadlySpikes::CheckPlayerDie);
	SpikeCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	bIsFly = true;
	bFlyDown = false;
	GetWorldTimerManager().SetTimer(BeforeFlyDownTimer, this, &ADeadlySpikes::PauseBeforeFlyDown, FlyTime);
}

void ADeadlySpikes::CheckPlayerDie(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsEnabled)
	{
		bIsEnabled = false;
		auto Player = Cast<AMainCharacter>(OtherActor);
		if (Player)
		{
			Player->CharacterDied();
		}
	}

}

// Called every frame
void ADeadlySpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsFly)
	{
		Spikes->SetWorldLocation(Spikes->GetComponentLocation() + FVector(0.0f, 0.0f, FlySpeed) * DeltaTime * (bFlyDown ? -1.f : 1.f), false);
	}
}

