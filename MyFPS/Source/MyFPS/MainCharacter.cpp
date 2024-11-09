// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EPICCube.h"
#include "StandForCube.h"

// Sets default values
AMainCharacter::AMainCharacter() :
	bIsLive(true),
	IsDisableInput(false),
	NumberOfInteractActor(0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1.f;
	CameraBoom->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollCam"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// lock rotation by controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	ForCube0 = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube0"));
	ForCube0->SetupAttachment(RootComponent);
	ForCube1 = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube1"));
	ForCube1->SetupAttachment(RootComponent);
	ForCube2 = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube2"));
	ForCube2->SetupAttachment(RootComponent);

}

void AMainCharacter::CharacterDied()
{
	if (bIsLive)
	{
		bIsLive = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("U Died"));//возможно сделать какое-нибудь уведомление
		GetMesh()->SetSimulatePhysics(true);//включаем физику у перса
		SetIsDisableInput(true);//отключаем управление

		if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent()) {
			CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CapsuleComp->SetGenerateOverlapEvents(false);
		}

		//LoadSaveDeath();
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		CameraManager->StartCameraFade(0.f, 1.f, 3.f, FColor::Black, false, true);//включаем тень на камере
		FollowCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void AMainCharacter::CharacterStop(bool condition)
{
	(condition) ? GetCharacterMovement()->DisableMovement() : GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::MoveRight(float Value)
{
	if (IsDisableInput) {
		return;
	}
	if ((Controller != nullptr) && (Value != 0.0f)) {
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveForward(float Value)
{
	if (IsDisableInput) {
		return;
	}
	if ((Controller != nullptr) && (Value != 0.0f)) {
		//search and calculate vector for move forward + move forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::CalculateCharacterValues(float DeltaTime)
{
	FVector XYspeed{ GetVelocity() };
	XYspeed.Z = 0;
	Speed = XYspeed.Size();
}

void AMainCharacter::CalculateCameraPosition(float DeltaTime)
{
}

void AMainCharacter::TryToInteract()
{
	GetWorld()->LineTraceSingleByChannel(OutHitResult, this->GetActorLocation() + this->GetActorForwardVector() * 10.f, this->GetActorLocation() + this->GetActorForwardVector() * 200.f, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(), this->GetActorLocation() + this->GetActorForwardVector() * 10.f, this->GetActorLocation() + this->GetActorForwardVector() * 200.f, FColor::Cyan, false, 3.f);
	if (OutHitResult.bBlockingHit) {
		ActorToInteract = Cast<AEPICCube>(OutHitResult.GetActor());
		if (ActorToInteract) {
			AttachCubeByRef(ActorToInteract);
		}
	}
	if (ActorForInteract != nullptr)
	{
		ActorToInteract = Cast<AEPICCube>(ActorForInteract);
		if (ActorToInteract) {
			AttachCubeByRef(ActorToInteract);
		}
	}
}

void AMainCharacter::TryToUNInteract()
{
	if (Stand != nullptr && NumberOfInteractActor > 0)
	{
		if (Stand)
		{

		}
	}
}

void AMainCharacter::AttachCubeByRef(AEPICCube* cube)
{
	if (NumberOfInteractActor < 3)
	{
		cube->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));
		cube->PickUp(true);
		if (NumberOfInteractActor == 0)
		{
			cube->AttachToComponent(ForCube0, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		else if (NumberOfInteractActor == 1)
		{
			cube->AttachToComponent(ForCube1, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		else if (NumberOfInteractActor == 2)
		{
			cube->AttachToComponent(ForCube2, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		InteractActors[NumberOfInteractActor] = cube;
		NumberOfInteractActor += 1;
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateCharacterValues(DeltaTime);
	CalculateCameraPosition(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveForward);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::TryToInteract);
	PlayerInputComponent->BindAction("UnInteract", IE_Pressed, this, &AMainCharacter::TryToUNInteract);
	//PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::StopInteract);
}

