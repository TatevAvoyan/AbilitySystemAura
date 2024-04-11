// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	if (UCharacterMovementComponent* L_MovementComponent = GetCharacterMovement(); IsValid(L_MovementComponent))
	{
		L_MovementComponent->bOrientRotationToMovement = true;
		L_MovementComponent->RotationRate = FRotator(0.f, 400.f, 0.f);
		L_MovementComponent->bConstrainToPlane = true;
		L_MovementComponent->bSnapToPlaneAtStart = true;

		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = false;
	}
}
