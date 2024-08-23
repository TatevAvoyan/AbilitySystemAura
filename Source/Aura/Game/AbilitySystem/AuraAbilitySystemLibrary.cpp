// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Game/Characters/PlayerState/AuraPlayerState.h"
#include "Game/UI/HUD/AuraHUD.h"
#include "Game/UI/WidgetController/AuraWidgetController/AuraWidgetController.h"
#include "Kismet/GameplayStatics.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0); IsValid(PC))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			if (AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>(); IsValid(PS))
			{
				UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
				UAttributeSet* AS = PS->GetAttributeSet();
				const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
				return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
			}
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0); IsValid(PC))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			if (AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>(); IsValid(PS))
			{
				UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
				UAttributeSet* AS = PS->GetAttributeSet();
				const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
				return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
			}
		}
	}

	return nullptr;
}
