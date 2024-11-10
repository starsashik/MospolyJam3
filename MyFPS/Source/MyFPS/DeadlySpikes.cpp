// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadlySpikes.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADeadlySpikes::ADeadlySpikes() :
	FlyTime(2.f),
	PauseTime(5.f),
	bFlyDown(false),
	bReverse(false)
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
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 2;
	LatentInfo.Linkage = 2;
	LatentInfo.ExecutionFunction = FName("PauseBeforeFlyDown");
	if (SpikeSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SpikeSound, Spikes->GetComponentLocation());
	}
	if (bFlyDown)
	{
		UKismetSystemLibrary::MoveComponentTo(Spikes, InitialLocation - DeltaLocation, FRotator(0.f, 0.f, 0.f), true, true, FlyTime, false, EMoveComponentAction::Move, LatentInfo);

	}
	else
	{
		UKismetSystemLibrary::MoveComponentTo(Spikes, InitialLocation, FRotator(0.f, 0.f, 0.f), true, true, FlyTime, false, EMoveComponentAction::Move, LatentInfo);
	}
}

void ADeadlySpikes::PauseBeforeFlyDown()
{
	bFlyDown = !bFlyDown;
	GetWorldTimerManager().ClearTimer(FlyDownTimer);
	GetWorldTimerManager().SetTimer(FlyDownTimer, this, &ADeadlySpikes::Fly, PauseTime);
}
void ADeadlySpikes::StartForReverse()
{
	bFlyDown = true;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 1;
	LatentInfo.ExecutionFunction = FName("PauseBeforeFlyDown");
	UKismetSystemLibrary::MoveComponentTo(Spikes, InitialLocation - DeltaLocation, FRotator(0.f, 0.f, 0.f), true, true, FlyTime, false, EMoveComponentAction::Move, LatentInfo);
}
// Called when the game starts or when spawned
void ADeadlySpikes::BeginPlay()
{
	Super::BeginPlay();
	SpikeCollision->OnComponentBeginOverlap.AddDynamic(this, &ADeadlySpikes::CheckPlayerDie);
	SpikeCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	InitialLocation = Spikes->GetRelativeLocation();


	if (bReverse)
	{
		GetWorldTimerManager().ClearTimer(TimerReverse);
		GetWorldTimerManager().SetTimer(TimerReverse, this, &ADeadlySpikes::StartForReverse, PauseTime + FlyTime);
	}
	else
	{
		bFlyDown = true;
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.UUID = 1;
		LatentInfo.Linkage = 1;
		LatentInfo.ExecutionFunction = FName("PauseBeforeFlyDown");
		UKismetSystemLibrary::MoveComponentTo(Spikes, InitialLocation - DeltaLocation, FRotator(0.f, 0.f, 0.f), true, true, FlyTime, false, EMoveComponentAction::Move, LatentInfo);
	}
}

void ADeadlySpikes::CheckPlayerDie(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<AMainCharacter>(OtherActor);
	if (Player)
	{
		Player->CharacterDied();
		Player->GetMesh()->AddImpulse(FVector(0.f,0.f,200.f), NAME_None, true);
	}
}

// Called every frame
void ADeadlySpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

