// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

/**
 * A structure used to define input actions and associated gameplay tags for the Aura game system.
 *
 * This structure binds an input action to a corresponding gameplay tag. It is primarily used in the context
 * of input handling in the Aura game. The input actions can be tied to various abilities or actions
 * performed by the player, with the gameplay tag acting as an identifier for the behavior or action associated
 * with the input.
 *
 * Properties:
 * - InputAction: A pointer to the UInputAction object corresponding to a specific input action.
 * - InputTag: An FGameplayTag used to identify the action or ability linked to the input.
 */
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * A configuration class for managing input actions and their associated gameplay tags in the Aura game system.
 *
 * This class serves as a data asset for defining mappings between input actions and gameplay tags. It enables the
 * handling of ability-related input through the gameplay tags, providing flexibility in managing and binding player actions.
 * It is primarily used for input handling, ability triggering, and dynamic configuration of input behaviors.
 *
 * Public Methods:
 * - FindAbilityInputActionForTag: Searches for the input action associated with a specific gameplay tag.
 *
 * Properties:
 * - AbilityInputActions: An array of input actions and their gameplay tag mappings for ability input configuration.
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * Finds and retrieves the input action associated with a specific gameplay tag.
	 *
	 * This method iterates through a collection of input actions and their corresponding gameplay tags to find a match for the given tag.
	 * If a matching input action is not found and logging is enabled, an error message is logged.
	 *
	 * @param InputTag The gameplay tag used to search for the associated input action.
	 * @param bLogNotFound A boolean flag indicating whether an error message should be logged if no matching input action is found.
	 * @return A pointer to the UInputAction object associated with the given gameplay tag. Returns nullptr if no match is found.
	 */
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	/**
	 * An array that holds mappings between input actions and gameplay tags for defining ability input configurations.
	 *
	 * This array contains FAuraInputAction structures, which link specific input actions to unique gameplay tags.
	 * It is used to define and manage the input actions associated with abilities or other gameplay mechanics,
	 * allowing dynamic binding and response to player actions.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;
};
