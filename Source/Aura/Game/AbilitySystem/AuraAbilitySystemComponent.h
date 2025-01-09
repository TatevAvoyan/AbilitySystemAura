// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

/**
 * @brief Custom ability system component for the Aura game.
 *
 * This component extends the basic UAbilitySystemComponent with additional functionality specific to the Aura game.
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	/**
	 * @brief Configures the Ability System Component when AbilityActor info is set.
	 *
	 * This method binds the EffectApplied callback to the OnGameplayEffectAppliedDelegateToSelf delegate,
	 * allowing the component to handle effects applied to itself.
	 */
public:
	void AbilityActorInfoSet();

	/**
	 * @brief Delegate for broadcasting effect asset tags.
	 *
	 * This delegate is used to broadcast the gameplay effect asset tags when a gameplay effect is applied to this ability system component.
	 * It is populated by extracting the asset tags from the effect specification during the effect application process.
	 */
	FEffectAssetTags EffectAssetTags;

	/**
	 * @brief Adds initial abilities to the character's ability system component.
	 *
	 * This method takes a list of gameplay abilities specified by their class type, constructs ability specifications
	 * for each, assigns any startup input tags they might have, and grants these abilities to the ability system component.
	 *
	 * @param StartupAbilities An array containing the classes of gameplay abilities to be added to the character.
	 */
	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InInputTag);
	void AbilityInputTagReleased(const FGameplayTag& InInputTag);
	
protected:
	/**
	 * @brief Callback for when a gameplay effect is applied to this ability system component.
	 *
	 * This method is triggered when a gameplay effect is successfully applied to the component.
	 * It extracts the asset tags from the effect specification and broadcasts them.
	 *
	 * @param AbilitySystemComponent The ability system component to which the effect is applied.
	 * @param EffectSpec The gameplay effect specification containing the details of the applied effect.
	 * @param ActiveEffectHandle The handle for the active gameplay effect that was applied.
	 */
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
