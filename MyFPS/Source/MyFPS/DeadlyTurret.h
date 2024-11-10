// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadlyTurret.generated.h"

UCLASS()
class MYFPS_API ADeadlyTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeadlyTurret();

	void Fire();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFireAnim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Turret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowprivateAccess = "true"))
	TSubclassOf<class AProjectileForTurret> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowprivateAccess = "true"))
	USoundBase* FireSound;

	FTimerHandle FireTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowprivateAccess = "true"))
	float FireSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ForBullet;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
