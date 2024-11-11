// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MainCharacter.generated.h"


UCLASS()
class MYFPS_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();


	UFUNCTION(BlueprintCallable)
	void CharacterDied();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);
	void MoveForward(float Value);

	void CalculateCharacterValues(float DeltaTime);

	void CalculateCameraPosition(float DeltaTime);



	void TryToInteract();

	void AttachCubeByRef(class AEPICCube* cube);

	void ShowDiedUI();

	void StartSitting();
	
	UFUNCTION(BlueprintCallable)
	void StopSitting();

	UFUNCTION(BlueprintImplementableEvent)
	void DashBP();

	void Dash();


private:
	//CameraSystem
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowprivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowprivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ForCube;

	//Character values
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterValues, meta = (AllowprivateAccess = "true"))
	float Speed;
	FHitResult OutHitResult;

	class AEPICCube* PrevInteractActor;
	class AEPICCube* ActorToInteract;

	class AStandForCube* Stand;

	bool bIsLive;

	bool IsDisableInput;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> DiedUICLass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	UUserWidget* DiedUI;

	FTimerHandle TimerBeforeDiedUI;

	bool bIsSitting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* SittingMontage;

	APlayerController* PlayerControler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowprivateAccess = "true"))
	USoundBase* DieSound;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetActorToInteract(class AEPICCube* actor) { ActorToInteract = actor; };
	FORCEINLINE void SetNearStand(class AStandForCube* standd) { Stand = standd; };
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsDisableInput() const { return IsDisableInput; };
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsDisableInput(bool value) { IsDisableInput = value; };
	
	UFUNCTION(BlueprintCallable)
	bool GetSitting() const { return bIsSitting; };

};
