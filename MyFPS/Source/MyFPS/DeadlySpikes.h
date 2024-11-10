// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadlySpikes.generated.h"

UCLASS()
class MYFPS_API ADeadlySpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeadlySpikes();

	void Fly();

	UFUNCTION()
	void PauseBeforeFlyDown();

	void StartForReverse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void CheckPlayerDie(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Spikes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpikeCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpikeParametr", meta = (AllowPrivateAccess = "true"))
	float FlyTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpikeParametr", meta = (AllowPrivateAccess = "true"))
	float PauseTime;

	FTimerHandle FlyDownTimer;
	FTimerHandle BeforeFlyDownTimer;
	FTimerHandle TimerReverse;

	FVector InitialLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpikeParametr", meta = (AllowPrivateAccess = "true"))
	FVector DeltaLocation;

	bool bFlyDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpikeParametr", meta = (AllowPrivateAccess = "true"))
	bool bReverse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowprivateAccess = "true"))
	USoundBase* SpikeSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
