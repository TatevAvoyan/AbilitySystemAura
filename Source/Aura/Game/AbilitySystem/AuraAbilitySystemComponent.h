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

	/**
	 * @brief Handles the logic for when an ability input tag is held.
	 *
	 * This function checks if the provided input tag is valid and iterates through the activatable abilities.
	 * If an ability matches the input tag and is not yet active, it attempts to activate the ability.
	 *
	 * @param InInputTag The gameplay tag representing the input held by the player.
	 */
	void AbilityInputTagHeld(const FGameplayTag& InInputTag);

	/**
	 * @brief Handles the release of an input associated with a gameplay ability.
	 *
	 * This function is responsible for iterating through the activatable abilities and identifying those
	 * that match the specified input tag. If a matching ability is found, the input release logic for that ability is executed.
	 *
	 * @param InInputTag The gameplay tag associated with the input that was released.
	 */
	void AbilityInputTagReleased(const FGameplayTag& InInputTag);
	
protected:
	/**
	 * @brief Notifies the client about an applied gameplay effect.
	 *
	 * This function is called on the client to provide information about a gameplay effect
	 * that was applied to an ability system component. It includes the effect specification
	 * and the handle representing the active effect.
	 *
	 * @param AbilitySystemComponent The ability system component to which the effect was applied.
	 * @param EffectSpec The specification of the gameplay effect that was applied.
	 * @param ActiveEffectHandle The handle representing the active gameplay effect.
	 */
	UFUNCTION(Client, Reliable)
	void Client_EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
