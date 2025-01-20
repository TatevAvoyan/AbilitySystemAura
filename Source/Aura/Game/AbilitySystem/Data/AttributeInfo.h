// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * FAuraAttributeInfo is a data structure that holds information related to specific in-game attributes.
 * It includes a gameplay tag for identification, a name and description for display purposes, and
 * a numerical value associated with the attribute.
 */
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	/**
	 * AttributeTag represents the gameplay tag associated with a specific attribute.
	 * It is used to identify and match the attribute within the attribute information system.
	 * This property is editable in defaults and accessible in blueprints.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	/**
	 * AttributeName represents the localized display name of an attribute.
	 * It is used for presenting a human-readable name for the attribute in the user interface.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	/**
	 * AttributeDescription provides a localized text description of the attribute.
	 * It is primarily used to display information about the attribute in user interfaces.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	/**
	 * AttributeValue represents the current numerical value of an attribute within the context
	 * of the gameplay attribute system. This variable is updated dynamically to reflect changes
	 * in the associated attribute, providing a means for tracking and displaying attribute states
	 * in systems or user interfaces leveraging the attribute menu functionality.
	 */
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * UAttributeInfo is a data asset class that contains information about various attributes.
 * It provides functions to find attribute information based on a given gameplay tag.
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * Searches for an attribute information entry that matches the given gameplay tag.
	 *
	 * @param AttributeTag The gameplay tag to search for within the attribute information entries.
	 * @param bLogNotFound If true, logs an error message if no matching attribute information is found.
	 * @return The attribute information entry that matches the given gameplay tag. Returns an empty FAuraAttributeInfo if no match is found.
	 */
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	/**
	 * An array holding information about various attributes. Each element in the array
	 * is of type FAuraAttributeInfo.
	 *
	 * The AttributeInformation array is only editable in the defaults and readable in blueprints.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
};
