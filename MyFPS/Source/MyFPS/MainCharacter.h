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

	UFUNCTION(BlueprintCallable)
	void CharacterStop(bool condition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);
	void MoveForward(float Value);

	void CalculateCharacterValues(float DeltaTime);

	void CalculateCameraPosition(float DeltaTime);



	void TryToInteract();

	void AttachCubeByRef(class AEPICCube* cube);


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterValues, meta = (AllowprivateAccess = "true"))
	AActor* ActorForInteract;
	FHitResult OutHitResult;

	class AEPICCube* PrevInteractActor;
	class AEPICCube* ActorToInteract;

	class AStandForCube* Stand;

	bool bIsLive;

	bool IsDisableInput;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetActorToInteract(AActor* actor) { ActorForInteract = actor; };
	FORCEINLINE void SetNearStand(class AStandForCube* standd) { Stand = standd; };
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsDisableInput() { return IsDisableInput; };
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsDisableInput(bool value) { IsDisableInput = value; };

};
