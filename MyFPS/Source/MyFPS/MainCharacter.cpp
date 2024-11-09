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
#include "MainGameModeBase.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AMainCharacter::AMainCharacter() :
	bIsLive(true),
	IsDisableInput(false)
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

	ForCube = CreateDefaultSubobject<USceneComponent>(TEXT("ForCube"));
	ForCube->SetupAttachment(RootComponent);
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
			CapsuleComp->SetGenerateOverlapEvents(false);
		}

		//LoadSaveDeath();
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		CameraManager->StartCameraFade(0.f, 1.f, 3.f, FColor::Black, false, true);//включаем тень на камере
		FollowCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		GetWorldTimerManager().SetTimer(TimerBeforeDiedUI, this, &AMainCharacter::ShowDiedUI, 3.3f);
	}
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
	Speed = XYspeed.Size() / 10.f;
}

void AMainCharacter::CalculateCameraPosition(float DeltaTime)
{
}

void AMainCharacter::TryToInteract()
{
	if (Stand != nullptr)
	{
		auto StandCube = Cast<AEPICCube>(Stand->GetInteractActor());
		bool proverka = false;
		if (PrevInteractActor != nullptr)
		{
			PrevInteractActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Stand->AttachCubeByRef(PrevInteractActor);
			PrevInteractActor = nullptr;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("-1"));
			proverka = true;
		}
		if (StandCube)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("+1"));
			StandCube->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			AttachCubeByRef(StandCube);	
			if (!proverka)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("!="));
				Stand->DetachCubeByRef();
			}
		}
	}
	else if (ActorToInteract != nullptr)
	{
		AttachCubeByRef(ActorToInteract);
	}
}

void AMainCharacter::AttachCubeByRef(AEPICCube* cube)
{
	if (PrevInteractActor != nullptr)
	{
		PrevInteractActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PrevInteractActor->SetActorTransform(cube->GetActorTransform());
		PrevInteractActor->PickUp(false);
	}
	cube->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));
	cube->PickUp(true);
	cube->AttachToComponent(ForCube, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ActorToInteract = PrevInteractActor;
	PrevInteractActor = cube;
	if (ActorToInteract != nullptr)
	{
		ActorToInteract->ShowMyWidget(true);
	}
}

void AMainCharacter::ShowDiedUI()
{
	auto MyGameMode = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	MyGameMode->MyPauseGame(1);
	if (DiedUICLass) {
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		DiedUI = CreateWidget<UUserWidget>(PlayerController, DiedUICLass);
		if (DiedUI) {
			DiedUI->AddToViewport();
			DiedUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMainCharacter::StartSitting()
{
	bIsSitting = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && SittingMontage) {
		AnimInstance->Montage_Play(SittingMontage);
		AnimInstance->Montage_JumpToSection(FName("Teleport"));
	}

	SetIsDisableInput(true);
}

void AMainCharacter::StopSitting()
{
	bIsSitting = false;

	SetIsDisableInput(false);
}

void AMainCharacter::Dash()
{
	DashBP();
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

	PlayerInputComponent->BindAction("Sitting", IE_Pressed, this, &AMainCharacter::StartSitting);
	PlayerInputComponent->BindAction("Sitting", IE_Released, this, &AMainCharacter::StopSitting);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMainCharacter::Dash);
	
}

