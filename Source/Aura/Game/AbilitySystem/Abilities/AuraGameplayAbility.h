// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * UAuraGameplayAbility is an extension of the UGameplayAbility class.
 * This class includes properties and functions specific to the Aura system's gameplay abilities.
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	/**
	 * This property holds a Gameplay Tag used for categorizing and identifying
	 * input for gameplay abilities. It is editable only in the defaults of the
	 * class and falls under the "Input" category.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
};
