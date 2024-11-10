// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadlyTurret.h"
#include "ProjectileForTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ADeadlyTurret::ADeadlyTurret():
	FireSpeed(3.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Turret = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Turrets"));
	Turret->SetupAttachment(RootComponent);
	ForBullet = CreateDefaultSubobject<USceneComponent>(TEXT("ForBullet"));
	ForBullet->SetupAttachment(Turret);
}

void ADeadlyTurret::Fire()
{
	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = ForBullet->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ForBullet->GetComponentLocation();
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			World->SpawnActor<AProjectileForTurret>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Turret->GetComponentLocation());
	}
	PlayFireAnim();
}

// Called when the game starts or when spawned
void ADeadlyTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FireTimer, this, &ADeadlyTurret::Fire, FireSpeed, true);
}

// Called every frame
void ADeadlyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

