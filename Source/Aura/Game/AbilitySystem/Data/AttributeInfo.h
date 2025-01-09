// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

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

	/**
	 * Searches for an attribute information entry that matches the given gameplay tag.
	 *
	 * @param AttributeTag The gameplay tag to search for within the attribute information entries.
	 * @param bLogNotFound If true, logs an error message if no matching attribute information is found.
	 * @return The attribute information entry that matches the given gameplay tag. Returns an empty FAuraAttributeInfo if no match is found.
	 */
public:
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
