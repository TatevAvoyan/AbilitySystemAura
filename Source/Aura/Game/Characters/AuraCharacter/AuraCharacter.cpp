// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aura/Game/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Game/Characters/PlayerController/AuraPlayerController.h"
#include "Aura/Game/Characters/PlayerState/AuraPlayerState.h"
#include "Aura/Game/UI/HUD/AuraHUD.h"
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

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();

	if (AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); IsValid(AuraPlayerState))
	{
		AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

		Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();

		if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
		{
			if (AAuraHUD* L_AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
			{
				L_AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			}
		}
	}
	InitializeDefaultAttributes();
}

int32 AAuraCharacter::GetPlayerLevel()
{
	int32 R_Level = 0;
	if (const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); IsValid(AuraPlayerState))
	{
		R_Level = AuraPlayerState->GetPLayerLevel();
	}

	return R_Level;
}
