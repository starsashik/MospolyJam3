// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMainAnimInstance::UMainAnimInstance():
	Speed(0.f),
	MAX_Stamina(10500.f),
	Stamina(10500.f),
	PreviousVelocity(0.f)
{
}

void UMainAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (MainCharacter == nullptr) {
		MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	}
	if (MainCharacter) {
		// speed without Z coords
		FVector Velocity{ MainCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		if (MainCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f) {
			bIsAccelerating = true;
		}
		else {
			bIsAccelerating = false;
		}


		AccelerationVector = (Velocity - PreviousVelocity) / DeltaTime;
		FMatrix ObjectRotationMatrix = MainCharacter->GetMesh()->GetComponentTransform().ToMatrixNoScale();
		AccelerationVector = ObjectRotationMatrix.Inverse().TransformVector(AccelerationVector);


		PreviousVelocity = Velocity;
		FRotator AimRotation = MainCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MainCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		if (MainCharacter->GetVelocity().Size() > 0.f) {
			LastMovementOffsetYaw = MovementOffsetYaw;
		}

		if ((Stamina - Speed * DeltaTime) < 0) {
			Stamina = 0;
		}
		else {
			Stamina -= Speed * DeltaTime;
		}
		if (Stamina + 100.f * DeltaTime > MAX_Stamina) {
			Stamina = MAX_Stamina;
		}
		else
		{
			Stamina += 100.f * DeltaTime;
		}
		//RightLeft = MainCharacter->GetRorL();
	}
	Lean(DeltaTime);
}

void UMainAnimInstance::NativeInitializeAnimation()
{
	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
}

void UMainAnimInstance::Lean(float DeltaTime)
{
	if (MainCharacter == nullptr) return;
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = MainCharacter->GetActorRotation();

	FRotator Delta{ UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame) };

	const float Target{ float(Delta.Yaw) / DeltaTime };

	const float Interp{ FMath::FInterpTo(YawDelta, Target, DeltaTime, 3.f) };

	YawDelta = FMath::Clamp(Interp, -90.f, 90.f);
}
