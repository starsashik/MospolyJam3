// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMainAnimInstance::UMainAnimInstance():
	Speed(0.f)
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
	}
}

void UMainAnimInstance::NativeInitializeAnimation()
{
	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
}
